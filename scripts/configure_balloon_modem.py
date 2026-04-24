#!/usr/bin/env python3

import serial
import time
import random
import sys

r1 = serial.Serial("/dev/ttyUSB0", baudrate=9600, timeout=0)

def query(r, cmd):
	r.write(cmd + b"\r")
	time.sleep(0.1)
	reply = r.read(100)
	print(r.port, cmd, reply)
	if b"ERROR" in reply:
		sys.stderr.write("WARNING: %r returned ERROR\n" % cmd)
	return reply

def enter_at_mode(r):
	query(r, b"ATO")
	time.sleep(0.2)
	for _ in range(3):
		print("sending +++ to %s" % r.port)
		r.write(b"+++")
		time.sleep(0.1)
		r.read(16)
		time.sleep(1.0)
		maybe_ok = r.read(16).strip()
		if maybe_ok == b"OK":
			print("AT mode entered")
			return True
	return False

def settings():
	enter_at_mode(r1)
	query(r1, b"")
	# ATS0 (FORMAT) is not user-settable, firmware rejects it — skipped.
	query(r1, b"ATS1=9")		# SERIAL_SPEED: 9600 baud (balloon side)
	query(r1, b"ATS2=2")		# AIR_SPEED: 2 kbps — max sensitivity
	query(r1, b"ATS3=25")		# NETID (must match GCS)
	query(r1, b"ATS4=20")		# TXPOWER: 20 dBm = 100 mW = TFSIK max
	query(r1, b"ATS5=0")		# ECC: no-op on Si1060 (INCLUDE_GOLAY off)
	query(r1, b"ATS6=1")		# MAVLINK framing on
	query(r1, b"ATS7=0")		# OPPRESEND off
	query(r1, b"ATS8=434050")	# MIN_FREQ
	query(r1, b"ATS9=434051")	# MAX_FREQ
	query(r1, b"ATS10=10")		# NUM_CHANNELS (ignored, hopping disabled)
	query(r1, b"ATS11=100")		# DUTY_CYCLE (ignored in one-way mode)
	query(r1, b"ATS12=0")		# LBT_RSSI off
	query(r1, b"ATS13=0")		# MANCHESTER: no-op on Si1060
	query(r1, b"ATS14=0")		# RTSCTS off
	query(r1, b"ATS15=131")		# MAX_WINDOW
	query(r1, b"ATS16=1")		# RX_TX: 1 = transmitter (balloon)
	query(r1, b"AT&W")
	query(r1, b"ATZ")
	time.sleep(0.5)
	query(r1, b"ATO")

def	main():
	settings()
	return

if __name__ == "__main__":
	main()
