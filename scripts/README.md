# Scripts — SiK modem provisioning for the one-way link

Helper scripts for configuring a TFSIK01 / ISM01A pair flashed with the
`one_direction_2026` one-way firmware. The scripts open `/dev/ttyUSB0`
by default — edit the `serial.Serial(...)` line at the top if you use
a different port.

## Configuration scripts

| Script | Role | Serial baud | AT parameter `RX_TX` |
|---|---|---|---|
| `configure_balloon_modem.py` | transmitter (balloon / sonde) | 9600 | 1 |
| `configure_gcs_modem.py` | receiver (ground control station) | 57600 | 0 |

Both scripts enter AT command mode (`+++`), push the full parameter
set (`ATS1`–`ATS16`), persist it with `AT&W`, and reset the modem
with `ATZ`. Shared parameters (air speed, NETID, frequency range,
MAVLink framing) are identical on both sides; the only difference
between balloon and GCS is `RX_TX`, `SERIAL_SPEED` and `TXPOWER`.

If any AT command returns `ERROR`, the scripts print a `WARNING` to
stderr but keep going.

## Utilities

| Script | What it does |
|---|---|
| `check_modem.py` | Opens port at 57600, enters AT mode, prints `ATI`, `ATI5`, `ATI6` (banner, all parameters, timing report), then `ATZ` + `ATO`. |
| `set57600.py` | Opens port at 9600 (current balloon-side speed), sets `ATS1=57`, `AT&W`, `ATZ`. Use to convert a 9600 baud modem to 57600. |
| `set9600.py` | Opens port at 57600 (current GCS-side speed), sets `ATS1=9`, `AT&W`, `ATZ`. Use to convert a 57600 baud modem to 9600. |

## Parameters that don't do anything on Si1060

Both configuration scripts still set `ATS5=0` (ECC) and `ATS13=0`
(MANCHESTER) explicitly. On Si1060 (TFSIK01, ISM01A) both parameters
are effectively **no-ops** with the current firmware:

- `INCLUDE_GOLAY` is commented out in `Firmware/radio/radio_446x.c`,
  so Golay encoding/decoding is never compiled in even if `ECC=1` is
  stored.
- `PARAM_MANCHESTER` has a slot in the parameter table but nothing in
  the Si446x code path reads it.

The scripts set them to 0 mainly as documentation; do not expect
`ATS5=1` or `ATS13=1` to improve the link.

## Typical workflow

1. Flash both modems with the `one_direction_2026` firmware (see
   `README.markdown` in the repo root for the `uploader.py` steps).
2. Plug the balloon modem into the USB-UART adapter, run
   `./configure_balloon_modem.py`.
3. Repeat with the GCS modem and `./configure_gcs_modem.py`.
4. Verify with `./check_modem.py` that `ATI5` shows the expected
   values on each side — particularly `S16` (`RX_TX`).
