#!/usr/bin/env python
# RSSI production test

import serial, sys, optparse, time
import pexpect.fdpexpect as fdpexpect

parser = optparse.OptionParser("update_mode")
parser.add_option("--baudrate", type='int', default=57600, help='baud rate')
parser.add_option("--rtscts", action='store_true', default=False, help='enable rtscts')
parser.add_option("--dsrdtr", action='store_true', default=False, help='enable dsrdtr')
parser.add_option("--xonxoff", action='store_true', default=False, help='enable xonxoff')

opts, args = parser.parse_args()

if len(args) == 0:
    print("usage: rssi.py <DEVICE...>")
    sys.exit(1)


def flush(ser):
    '''discard everything currently pending, both in pexpect's own buffer
    and in the underlying serial input buffer'''
    try:
        ser.expect(fdpexpect.TIMEOUT, timeout=0.5)
    except fdpexpect.EOF:
        pass


def rssi(device):
    port = serial.Serial(
        device,
        opts.baudrate,
        timeout=0,
        dsrdtr=opts.dsrdtr,
        rtscts=opts.rtscts,
        xonxoff=opts.xonxoff
    )

    ser = fdpexpect.fdspawn(port.fileno(), encoding="latin-1")
    # logfile_read (not logfile) so we echo only what the modem sends back,
    # otherwise every command we send is printed twice.
    ser.logfile_read = sys.stdout
    ser.send('+++')
    time.sleep(1)
    # '+++' makes the modem print "OK" and switch to command mode. Drop that
    # reply (and any stale line noise) so the ATI response below is matched
    # against the version banner only, not against the leftover "OK".
    flush(ser)
    ser.send('\r\nATI\r\n')
    try:
        ser.expect('SiK .*', timeout=2)
    except fdpexpect.TIMEOUT:
        print("timeout")
        return
    # Let the banner finish and drain it; otherwise AT&F is sent while the
    # modem is still transmitting and is received corrupted.
    flush(ser)
    ser.send('AT&F\r\n')
    try:
        ser.expect('OK', timeout=2)
    except fdpexpect.TIMEOUT:
        print("timeout")
        return

    ser.send('AT&T=RSSI\r\n')

    ctr = 0

    while ctr < 200:
        try:
            count = port.inWaiting()
            if count == 0:
                count = 1
            buf = port.read(count)
            if len(buf) == 0:
                continue
            if isinstance(buf, bytes):
                buf = buf.decode('utf-8', errors='replace')
            sys.stdout.write(buf)
            sys.stdout.flush()
            ctr = ctr + 1

        except KeyboardInterrupt:
            sys.exit(0)

    port.close()


for d in args:
    print(("Putting %s into rssi test mode" % d))
    rssi(d)
