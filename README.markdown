# SiK - Firmware for Telemetry data transfer with SiLabs Si102x/3x/6x ISM Transceivers

[![Build firmware](https://github.com/ThunderFly-aerospace/SiK/actions/workflows/build-firmware.yaml/badge.svg)](https://github.com/ThunderFly-aerospace/SiK/actions/workflows/build-firmware.yaml)

SiK is a collection of firmware and tools for UAV telemetry radios based on SiLabs Si1000 and Si1060 SoC Transceivers.

## Documentation
For user documentation, please see [ThunderFly docs](https://docs.thunderfly.cz/avionics/TFSIK01/)

Currently, it supports the following boards:

 - HopeRF HM-TRP
 - HopeRF RF50-DEMO
 - RFD900
 - RFD900u
 - RFD900p
 - [MLAB ISM01](https://www.mlab.cz/module/ISM01/) - Modular Laboratory Si1060 development module
 - [ThunderFly TFSIK01](https://github.com/ThunderFly-aerospace/TFSIK01) - UAV dual antenna diversity sub-GHz radio modem. 

Currently, the firmware components include:

 - A bootloader with support for firmware upgrades over the serial interface.
 - Radio firmware with support for parsing AT commands, storing parameters, and FHSS/TDM functionality
 - Set of tools for testing and configuration.

### How it works

The TFSIK01 telemetry modem operates using a combination of Frequency Hopping Spread Spectrum ([FHSS](https://en.wikipedia.org/wiki/Frequency-hopping_spread_spectrum)) and adaptive Time Division Multiplexing ([TDM](https://en.wikipedia.org/wiki/Time-division_multiplexing)) with Gaussian Frequency Shift Keying ([GFSK](https://en.wikipedia.org/wiki/Frequency-shift_keying#Gaussian_frequency-shift_keying)) modulation. A combination of those methods provides a robust and interference-resistant radio communication link for UAV telemetry.

The FHSS implementation divides the user-specified frequency band between `MIN_FREQ + δ` and `MAX_FREQ - δ` into a defined number of discrete channels (`NUM_CHANNELS`), where δ is a guard value equal to half the calculated channel width. This ensures that the radio remains within the safe central portion of the frequency band, avoiding spurious emissions near the band edges. The channel width is determined by:

    channel_width = (MAX_FREQ - MIN_FREQ) / (NUM_CHANNELS + 2)

To provide frequency isolation between different network IDs (`NETID`), each modem applies a unique base frequency offset, up to one full channel width, derived from a pseudo-random seed based on the `NETID` value. This mechanism ensures that two radio links operating in the same physical space but with different `NETID` values will operate on slightly displaced sets of hopping frequencies.

To coordinate transmission and avoid collisions, the modem implements synchronous TDM. The radios divide time into discrete slices using a clock with a resolution of 16 µs. Each complete TDM cycle includes one radio's transmission slot, followed by a silence period, and then the other radio's transmission slot. The radios switch to the next frequency channel twice per TDM round.  The channel changes occur during each silence period. This approach guarantees that both radios never transmit simultaneously.

Clock synchronization between radios is achieved by embedding a 13-bit timestamp (in 16 µs units) in each transmitted packet. This allows both radios to maintain aligned timebases for TDM operation. The channel hopping sequence itself is randomized using a permutation based on `NETID`.

TDM parameters such as the transmission window and silence period are determined by stored parameter values and are scaled according to the selected data rate. These values are used to ensure regulatory compliance—particularly the maximum time of occupancy (dwell time) per frequency channel, which is limited to 0.4 seconds under U.S. rules.

The size of the transmit window is scaled to allow the transmission of up to three full MAVLink packets. The following silence period is set to twice the expected packet latency based on the configured data rate, which allows time for signal settling, and channel switching, and minimizes the chance of interference during transitions.

To manage serial data efficiently, the modem uses a 2048-byte buffer to hold incoming UART data. The modem monitors buffer fill levels and communicates this status back to the host system. Flight controller software like PX4 and Ardupilot can then adapt telemetry message rates dynamically to avoid overfilling the buffer and to optimize link latency.

The TDM implementation is adaptive: when one radio has no data to send during its slot, it can transfer control to the peer by sending a token indicating that it yields the remaining timeslice. This allows the link to automatically rebalance in response to asymmetric traffic loads.

During initial startup or after a link is lost, the radios enter a scanning mode. One radio transmits using its normal hopping pattern, while the receiver slowly steps through possible receive frequencies to locate the signal. Once detected, the receiver synchronizes its clock and begins coordinated TDM operation. The time required to re-establish a link depends on the number of hopping channels, the air data rate, and the current packet loss conditions.

### AT commands

|Command| Variants| Function |
|-------|--------|----------|
|+++    | |Entering command mode. This could be tested by sending AT; the reply should be OK. To prevent data from being seen as the command sequence, a guard time is required, so make sure you type nothing on the serial link for 1 second before and after entering the sequence.|
|RT     | |remote AT command - send it to the TDM, system to send to the remote radio |
|AT&F   | |  Restore default parameters |
|AT&W| | Write parameters to the flash memory | 
|AT&U | | Erase Flash signature forcing it into reprogram mode next reset |
|AT&P | | TDM change phase |
|AT&T | AT&T <br> AT&T=RSSI <br> AT&T=TDM |  disable all test modes <br> display RSSI stats <br> display TDM debug |
|AT&E | AT&E?  <br> AT&E= | Print_encryption_key <br> Set encryption key | 
|AT+ | AT+P= <br> AT+Cx=y <br> AT+Fx? <br> AT+L <br> AT+A |  set power level PWR to x immediately <br>  write calibration value <br> get calibration value <br> lock bootloader area if all calibrations written <br> Select antenna and override diversity  |
|ATI0| | banner_string |
|ATI1| | version_string  |
|ATI2| | BOARD_ID |
|ATI3| | Board design frequency|
|ATI4| | Board boot loader version|
|ATI5| | Show all user-configurable parameters |
|ATI6| | TDM timing report |
|ATI7| | Show RSSI report |
|ATP |  ATPx=O <br> ATPx=I <br> ATPx=R <br> ATPx=Cx | Set pin to output, turn mirroring off, pulling pin to ground    |
|ATO | |  Go on-air (exit command mode)  |
|ATS | ATS? <br> ATS= | <br> Set a parameter  |
|ATZ | | Generate a software reset    |

Up-to-date AT command processing is located in [at.c](Firmware/radio/at.c) source code.

#### Example of parameters read

    picocom /dev/ttyUSB0 -b 57600
    +++
    OK
    ATI5
    S0:FORMAT=26
    S1:SERIAL_SPEED=57
    S2:AIR_SPEED=64
    S3:NETID=25
    S4:TXPOWER=20
    S5:ECC=0
    S6:MAVLINK=1
    S7:OPPRESEND=0
    S8:MIN_FREQ=433050
    S9:MAX_FREQ=434790
    S10:NUM_CHANNELS=10
    S11:DUTY_CYCLE=100
    S12:LBT_RSSI=0
    S13:MANCHESTER=0
    S14:RTSCTS=0
    S15:MAX_WINDOW=131

#### Example of parameter write

Change the number of channels to one. (eg. disable channel hopping)

    ATS10=1
    OK
    ATI5
    S0:FORMAT=26
    S1:SERIAL_SPEED=57
    S2:AIR_SPEED=64
    S3:NETID=25
    S4:TXPOWER=20
    S5:ECC=0
    S6:MAVLINK=1
    S7:OPPRESEND=0
    S8:MIN_FREQ=433050
    S9:MAX_FREQ=434790
    S10:NUM_CHANNELS=1
    S11:DUTY_CYCLE=100
    S12:LBT_RSSI=0
    S13:MANCHESTER=0
    S14:RTSCTS=0
    S15:MAX_WINDOW=131
    AT&W
    OK
    ATZ

Change antenna diversity mode (specific command for [ThunderFly TFSIK01](https://docs.thunderfly.cz/avionics/TFSIK01/) with dual antenna): 

    AT+A=1
    OK
    AT+A=2
    OK
 
## What You Will Need for Development

 - A Mac OS X or Linux system for building.  Mac users will need the Developer Tools (Xcode) installed.
 - At least two Si1000 - Si102x/3x - based radio devices (just one radio by itself is not very useful).
 - A [SiLabs USB debug adapter](http://www.silabs.com/products/mcu/Pages/USBDebug.aspx).
 - [SDCC](http://sdcc.sourceforge.net/), version 3.1.0 or later.
 - [EC2Tools](https://github.com/ThunderFly-aerospace/ec2)
 - [Mono](http://www.mono-project.com/) to build and run the GUI firmware updater.
 - Python to run the command-line firmware updater.

Just so you know, at this time, building on Windows systems is not supported if someone wants to contribute and maintain the necessary pieces that would be wonderful.

## Building Things

Type `make install` in the Firmware directory.  If all is well, this will produce a folder called `dst` containing the bootloader and firmware images.

If you want to fine-tune the build process, `make help` will give you more details.

Building the SiK firmware generates bootloaders and firmware for each of the supported boards. Many boards are available, tuned to specific frequencies, but have no way for software on the Si1000 to detect which frequency the board is configured for. In this case, the build will produce different versions of the bootloader for each board. It's important to select the correct bootloader version for your board if this is the case.

## Flashing and Uploading

The SiLabs debug adapter can be used to flash both the bootloader and the firmware. Alternatively, once the bootloader has been flashed, the updater application can be used to update the firmware (it's faster than flashing, too).

The `Firmware/tools/ec2upload` script can be used to flash either a bootloader or firmware to an attached board with the SiLabs USB debug adapter.  Further details on the connections required to flash a specific board should be found in the `Firmware/include/board_*.h` header for the board in question.

To use the updater application, open the `SiKUploader/SikUploader.sln` Mono solution file, build and run the application. Select the serial port connected to your radio and the appropriate firmware `.hex` file for the firmware you wish to upload.  You will need to get the board into the bootloader; how you do this varies from board to board, but it will normally involve either holding down a button or pulling a pin high or low when the board is reset or powered on.

For the supported boards:

 - TFSIK01: Hold the BOOT/CTS pin low when applying power to the board.
 - HM-TRP: Hold the CONFIG pin low when applying power to the board.
 - RF50-DEMO: Hold the ENTER button down and press RST.
 - RFD900x: hold the BOOT/CTS pin low when applying power to the board.

The uploader application contains a bidirectional serial console that can be used for interacting with the radio firmware.

As an alternative to the Mono uploader, there is a Python-based command-line upload tool in `Firmware/tools/uploader.py`.

## Supporting New Boards

Take a look at `Firmware/include/board_*.h` for the details of what board support entails.  It will help to have a schematic for your board, and in the worst case, you may need to experiment a little to determine a suitable value for EZRADIOPRO_OSC_CAP_VALUE.  To set the frequency codes for your board, edit the corresponding `Firmware/include/rules_*.mk` file.

## Resources

SiLabs has an extensive collection of documentation, application notes, and sample code available online.

Start at the [Si1000 product page](http://www.silabs.com/products/wireless/wirelessmcu/Pages/Si1000.aspx) or [Si102x/3x product page](http://www.silabs.com/products/wireless/wirelessmcu/Pages/Si102x-3x.aspx)

## Reporting Problems

Please use the GitHub issues link at the top of the GitHub project page to report any problems with, or to make suggestions about SiK.  I encourage you to fork the project and make whatever use you may of it.

## What does SiK mean?

It should really be Sik, since 'K' is the SI abbreviation for Kelvin, and what I meant was 'k', i.e., 1000.
