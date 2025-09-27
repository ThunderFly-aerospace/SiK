#!/usr/bin/env python3

# This script generates radio/radio_446x_conf.h
# Copyright (c) 2022 ThunderFly s.r.o., All Rights Reserved
#
# Silabs' WDS software allows to export a header file containing register values
# for a specific configuration of the radio. For our use we want to be able to
# switch between couple of those configurations. That's where this script comes in.
# It compares a set of headers generated from WDS and compiles all the register
# values into a somewhat compressed format. As part of this format it singles out
# registers whose value does not change between all the considered configurations.

import argparse
import glob
import os
import re
import sys


def parse_args():
    parser = argparse.ArgumentParser(
        description="Generate Si446x configuration table from WDS headers",
    )
    parser.add_argument(
        "--config-dir",
        required=True,
        help="Directory with WDS generated configuration headers",
    )
    parser.add_argument(
        "--output",
        help="File to write the generated table to (defaults to stdout)",
    )
    return parser.parse_args()


def print_bytes(out, bytes_):
    out.write(", ".join(["0x%02x" % b for b in bytes_]))


def ids_list(indices):
    indices = sorted(indices)
    indices_starts = [k for k in indices if k - 1 not in indices]
    ret = []
    for i, k in enumerate(indices_starts):
        last = i == len(indices_starts) - 1
        l = len([k_ for k_ in indices if k_ >= k and (last or k_ < indices_starts[i + 1])])
        while l > 0:
            l_ = min(l, 12)
            ret += [l_, k // 256, k % 256]
            l -= l_
            k += l_
    return ret + [0]


def main():
    args = parse_args()

    config_dir = os.path.abspath(args.config_dir)
    headers = sorted(glob.glob(os.path.join(config_dir, "*.h")))

    if not headers:
        raise SystemExit(f"No header files found in {config_dir}")

    out = sys.stdout
    close_out = False
    if args.output:
        out = open(args.output, "w", encoding="utf-8")
        close_out = True

    propbytes = {}
    skip = ['RF_MODEM_RSSI_CONTROL_1', 'RF_MODEM_RSSI_COMP_1',
            'RF_MODEM_CLKGEN_BAND_1']

    for path in headers:
        fn = os.path.basename(path)
        with open(path, 'r', encoding="utf-8") as f:
            for d in re.finditer('\n#define (RF_[^ ]+) (.+)\n', f.read()):
                if d.group(1) in skip:
                    continue
                bytes_ = eval('[' + d.group(2) + ']')
                if bytes_[0] != 0x11:
                    continue
                group, off = bytes_[1], bytes_[3]
                # keep MODEM, MODEM_CHFLT, PA, SYNTH
                if group < 0x20 or group >= 0x30:
                    continue
                for i, v in enumerate(bytes_[4:]):
                    k = group * 256 + (off + i)
                    if k not in propbytes:
                        propbytes[k] = {}
                    propbytes[k][fn] = v

    if not propbytes:
        raise SystemExit(f"No modem property data found in {config_dir}")

    shared = sorted([k for k in propbytes if len(set(propbytes[k].values())) == 1])

    print("/* see tools/build_si446x_table.py */\n", file=out)

    print("__code static const uint8_t shared_prop_ids[] = {", file=out)
    out.write("\t")
    print_bytes(out, ids_list(shared))
    out.write("\n};\n\n")

    print("__code static const uint8_t shared_prop_vals[] = {", file=out)
    out.write("\t")
    print_bytes(out, [list(propbytes[k].values())[0] for k in shared])
    out.write("\n};\n\n")

    variable = sorted([k for k in propbytes if len(set(propbytes[k].values())) != 1])

    print("__code static const uint8_t variable_prop_ids[] = {", file=out)
    out.write("\t")
    print_bytes(out, ids_list(variable))
    out.write("\n};\n\n")

    bands = ["433", "868", "915"]
    rates = ["2", "4", "8", "16", "19", "24", "32",
             "48", "64", "96", "128", "192", "250"]

    for band in bands:
        print("__code static const uint8_t band_%s_prop_vals[%d][%d] = {" %
              (band, len(rates), len(variable)), file=out)
        for rate in rates:
            fn = "%s_%skbps.h" % (band, rate)
            missing = [k for k in variable if fn not in propbytes[k]]
            if missing:
                raise SystemExit(f"Missing header '{fn}' in {config_dir}")
            out.write("\t{")
            print_bytes(out, [propbytes[k][fn] for k in variable])
            out.write("}%s\n" % ("" if rate == "250" else ","))
        out.write("};\n\n")

    if close_out:
        out.close()


if __name__ == "__main__":
    main()
