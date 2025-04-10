// -*- Mode: C; c-basic-offset: 8; -*-
//
// Copyright (c) 2011 Michael Smith, All Rights Reserved
// Copyright (c) 2011 Andrew Tridgell, All Rights Reserved
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  o Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  o Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//

///
/// @file	_start.c
///
/// Early startup code.
/// This file *must* be linked first for interrupt vector generation and main() to work.
/// XXX this may no longer be the case - it may be sufficient for the interrupt vectors
/// to be located in the same file as main()
///

#include <stdarg.h>
#include "radio.h"
#include "tdm.h"
#include "timer.h"
#include "freq_hopping.h"

#ifdef INCLUDE_AES
#include "AES/aes.h"
#endif

////////////////////////////////////////////////////////////////////////////////
/// @name	Interrupt vector prototypes
///
/// @note these *must* be placed in this file for SDCC to generate the
/// interrupt vector table correctly.
//@{

/// Serial rx/tx interrupt handler.
///
extern void	serial_interrupt(void)	__interrupt(INTERRUPT_UART0);

/// Radio event interrupt handler.
///
extern void	Receiver_ISR(void)	__interrupt(INTERRUPT_INT0);

/// Timer2 tick interrupt handler
///
extern void    T2_ISR(void)     __interrupt(INTERRUPT_TIMER2);

/// Timer3 tick interrupt handler
///
/// @todo switch this and everything it calls to use another register bank?
///
extern void    T3_ISR(void)     __interrupt(INTERRUPT_TIMER3);

#ifdef INCLUDE_AES
extern void    DMA_ISR(void)    __interrupt(INTERRUPT_DMA0);
#endif // INCLUDE_AES

//@}

__code const char g_banner_string[] = "SiK " stringify(APP_VERSION) " on " BOARD_NAME;
__code const char g_version_string[] = stringify(APP_VERSION);

__pdata enum BoardFrequency	g_board_frequency;	///< board info from the bootloader
__pdata uint8_t			g_board_bl_version;	///< from the bootloader

/// Configure the Si1000 for operation.
///
static void hardware_init(void);

/// Initialise the radio and bring it online.
///
static void radio_init(void);

/// statistics for radio and serial errors
__pdata struct error_counts errors;
__pdata struct statistics statistics, remote_statistics;

/// optional features
bool feature_golay;
uint8_t feature_mavlink_framing;
bool feature_rtscts;

void
main(void)
{
#ifdef CPU_SI1030
	PSBANK = 0x33;
#endif
	
	// Stash board info from the bootloader before we let anything touch
	// the SFRs.
	//
	g_board_frequency = BOARD_FREQUENCY_REG;
	g_board_bl_version = BOARD_BL_VERSION_REG;

	// Load parameters from flash or defaults
	// this is done before hardware_init() to get the serial speed
	if (!param_load())
		param_default();

	// setup boolean features
	feature_mavlink_framing = param_get(PARAM_MAVLINK);
	feature_golay = param_get(PARAM_ECC)?true:false;
	feature_rtscts = param_get(PARAM_RTSCTS)?true:false;

	// Do hardware initialisation.
	hardware_init();

	// do radio initialisation
	radio_init();

	// turn on the receiver
	if (!radio_receiver_on()) {
		panic("failed to enable receiver");
	}

	// Init user pins
#if PIN_MAX > 0
	pins_user_init();
#endif
	
#ifdef INCLUDE_AES
	// Initialise Encryption
	if (! aes_init(param_get(PARAM_ENCRYPTION))) {
		panic("failed to initialise aes");
	}
#endif // INCLUDE_AES

	tdm_serial_loop();
}

void
panic(char *fmt, ...)
{
	va_list ap;

//	puts("\n**PANIC**");
	va_start(ap, fmt);
	vprintf(fmt, ap);
//	puts("");

	EA = 1;
	ES0 = 1;
	
	delay_msec(1000);

	// generate a software reset
	RSTSRC |= (1 << 4);
	for (;;)
		;
}

static void
hardware_init(void)
{
	__xdata uint16_t	i;

	// Disable the watchdog timer
	PCA0MD	&= ~0x40;

	// Select the internal oscillator, prescale by 1
#ifdef CPU_SI1030
	OSCICN	|=  0x80;
#else
	OSCICN	 =  0x8F;
#endif
	FLSCL	 =  0x40;
	CLKSEL	 =  0x00;

	// Configure the VDD brown out detector
	VDM0CN	 =  0x80;
	for (i = 0; i < 350; i++);	// Wait 100us for initialization
	RSTSRC	 =  0x06;		// enable brown out and missing clock reset sources

#if defined CPU_SI1030
	P0SKIP  =  0xCF;
	P1SKIP  =  0xFF;
#if defined BOARD_mro900
	P2SKIP  =  0xF8;				// P2 nothing avail on XBAR, All GPIO
#else
	P2SKIP  =  0x28;
#endif
#elif defined BOARD_rfd900a		// Redefine port skips to override bootloader defs
	P0SKIP  =  0xCF;				// P0 UART avail on XBAR
	P1SKIP  =  0xF8;				// P1 SPI1 avail on XBAR
	P2SKIP  =  0xCF;				// P2 CEX0 avail on XBAR P2.4, rest GPIO
#endif

	// Configure crossbar for UART
#if defined BOARD_3dr1060
	P0MDOUT   =  0x90;		// UART Tx push-pull and SDN
	SFRPAGE   =  CONFIG_PAGE;
	P0DRV     =  0x90;		// UART TX
	SFRPAGE   =  LEGACY_PAGE;
	XBR0      =  0x01;		// UART enable
#else
	P0MDOUT   =  0x10;		// UART Tx push-pull
	SFRPAGE   =  CONFIG_PAGE;
	P0DRV     =  0x10;		// UART TX
	SFRPAGE   =  LEGACY_PAGE;
	XBR0      =  0x01;		// UART enable
#endif

	// SPI1
#if defined CPU_SI1030
	XBR1    |= 0x41;	// Enable SPI1 (3 wire mode) + CEX0
	P2MDOUT |= 0xFD;	// SCK1, MOSI1, & NSS1,push-pull
#elif defined BOARD_rfd900a		// Redefine port skips to override bootloader defs
	XBR1    |= 0x41;	// enable SPI in 3-wire mode + CEX0
	P1MDOUT |= 0xF5;	// SCK1, MOSI1, MISO1 push-pull
	P2MDOUT |= 0xFF;	// SCK1, MOSI1, MISO1 push-pull
#elif defined BOARD_3dr1060
	XBR1    |= 0x40;	// enable SPI in 4-wire mode
	P1MDOUT |= 0xFD;	// SCK1, MOSI1, MISO1 push-pull
#else
	XBR1    |= 0x40;	// enable SPI in 3-wire mode
	P1MDOUT |= 0xF5;	// SCK1, MOSI1, MISO1 push-pull
#endif	
	
	/* ------------ Config Parameters ------------ */
	SFRPAGE	 = CONFIG_PAGE;
#if defined BOARD_3dr1060
	P1DRV	|= 0xFD;	// SPI signals use high-current mode, LEDs and PAEN High current drive
#else
	P1DRV	|= 0xF5;	// SPI signals use high-current mode, LEDs and PAEN High current drive
#endif	
	
#ifdef CPU_SI1030
	P2DRV	 = 0xFD; // MOSI1, SCK1, NSS1, high-drive mode
	
	P3MDOUT |= 0xC0;		/* Leds */
	P3DRV   |= 0xC0;		/* Leds */
#else
	P2DRV	|= 0xFF;
#endif
	
	/* ------------ Change to radio page ------------ */
	RADIO_PAGE();
	SPI1CFG  = 0x40;  // master mode
#if defined(BOARD_ism01a) || defined(BOARD_hb1060) || defined(BOARD_3dr1060) || defined(BOARD_tfsik01a)
        SPI1CN   = 0x0C;  // 4 wire master mode, NSS1=1
#else
        SPI1CN   = 0x00;  // 3 wire master mode
#endif
	SPI1CKR  = 0x00;  // Initialise SPI prescaler to divide-by-2 (12.25MHz, technically out of spec)
	SPI1CN  |= 0x01;  // enable SPI
	NSS1     = 1;     // set NSS high

	/* ------------ END of Config Parameters ------------ */
	SFRPAGE	 = LEGACY_PAGE;
	
	// Clear the radio interrupt state
	IE0	 = 0;

	// initialise timers
	timer_init();

	// UART - set the configured speed
	serial_init(param_get(PARAM_SERIAL_SPEED));

	// set interrupt priority level
	IP = 0;  // default low priority
	PS0 = 1; // UART0 high priority
	PT2 = 1; // TIMER2 high priority

	// global interrupt enable
	EA = 1;
	
	// Turn off the 'radio running' LED and turn off the bootloader LED
	LED_RADIO = LED_OFF;
	LED_BOOTLOADER = LED_OFF;

	// ADC system initialise for temp sensor
	AD0EN = 1;	// Enable ADC0
	ADC0CF = 0xF9;  // Set amp0gn=1 (1:1)
	ADC0AC = 0x00;
	ADC0MX = 0x1B;	// Set ADC0MX to temp sensor
	REF0CN = 0x07;	// Define reference and enable temp sensor

#if defined BOARD_rfd900a || defined BOARD_rfd900p
	// PCA0, CEX0 setup and enable.
	PCA0MD = 0x88;
	PCA0PWM = 0x00;
	PCA0CPM0 = 0x42;
	PCA0CPH0 = 0x80;
	PCA0CN = 0x40;
#endif
	XBR2	 =  0x40;		// Crossbar (GPIO) enable
}

static void
radio_init(void)
{
	__xdata uint32_t freq_min, freq_max;
	__xdata uint32_t channel_spacing;
	__xdata uint8_t txpower;

	// Do generic PHY initialisation
	if (!radio_initialise()) {
		panic("radio_initialise failed");
	}

	switch (g_board_frequency) {
	case FREQ_433:
		freq_min = 433050000UL;
		freq_max = 434790000UL;
		txpower = 10;
		num_fh_channels = 10;
		break;
	case FREQ_470:
		freq_min = 470000000UL;
		freq_max = 471000000UL;
		txpower = 10;
		num_fh_channels = 10;
		break;
	case FREQ_868:
		freq_min = 868000000UL;
		freq_max = 870000000UL;
		txpower = 10;
		num_fh_channels = 10;
		break;
	case FREQ_915:
		freq_min = 915000000UL;
		freq_max = 928000000UL;
		txpower = 20;
		num_fh_channels = MAX_FREQ_CHANNELS;
		break;
	default:
		freq_min = 0;
		freq_max = 0;
		txpower = 0;
		panic("bad board frequency %d", g_board_frequency);
		break;
	}

	if (param_get(PARAM_NUM_CHANNELS) != 0) {
		num_fh_channels = param_get(PARAM_NUM_CHANNELS);
	}
	if (param_get(PARAM_MIN_FREQ) != 0) {
		freq_min        = param_get(PARAM_MIN_FREQ) * 1000UL;
	}
	if (param_get(PARAM_MAX_FREQ) != 0) {
		freq_max        = param_get(PARAM_MAX_FREQ) * 1000UL;
	}
	if (param_get(PARAM_TXPOWER) != 0) {
		txpower = param_get(PARAM_TXPOWER);
	}

	// constrain power and channels
	txpower = constrain(txpower, BOARD_MINTXPOWER, BOARD_MAXTXPOWER);
	num_fh_channels = constrain(num_fh_channels, 1, MAX_FREQ_CHANNELS);

	// double check ranges the board can do
	switch (g_board_frequency) {
	case FREQ_433:
		freq_min = constrain(freq_min, 414000000UL, 460000000UL);
		freq_max = constrain(freq_max, 414000000UL, 460000000UL);
		break;
	case FREQ_470:
		freq_min = constrain(freq_min, 450000000UL, 490000000UL);
		freq_max = constrain(freq_max, 450000000UL, 490000000UL);
		break;
	case FREQ_868:
		freq_min = constrain(freq_min, 849000000UL, 889000000UL);
		freq_max = constrain(freq_max, 849000000UL, 889000000UL);
		break;
	case FREQ_915:
		freq_min = constrain(freq_min, 868000000UL, 935000000UL);
		freq_max = constrain(freq_max, 868000000UL, 935000000UL);
		break;
	default:
		panic("bad board frequency %d", g_board_frequency);
		break;
	}

	if (freq_max == freq_min) {
		freq_max = freq_min + 1000000UL;
	}

	// get the duty cycle we will use
	duty_cycle = param_get(PARAM_DUTY_CYCLE);
	duty_cycle = constrain(duty_cycle, 0, 100);
	param_set(PARAM_DUTY_CYCLE, duty_cycle);

	// get the LBT threshold we will use
	lbt_rssi = param_get(PARAM_LBT_RSSI);
	if (lbt_rssi != 0) {
		// limit to the RSSI valid range
		lbt_rssi = constrain(lbt_rssi, 25, 220);
	}
	param_set(PARAM_LBT_RSSI, lbt_rssi);

	// sanity checks
	param_set(PARAM_MIN_FREQ, freq_min/1000);
	param_set(PARAM_MAX_FREQ, freq_max/1000);
	param_set(PARAM_NUM_CHANNELS, num_fh_channels);

	channel_spacing = (freq_max - freq_min) / (num_fh_channels+2);

	// add half of the channel spacing, to ensure that we are well
	// away from the edges of the allowed range
	freq_min += channel_spacing/2;

	// add another offset based on network ID. This means that
	// with different network IDs we will have much lower
	// interference
        r_srand(param_get(PARAM_NETID));
	if (num_fh_channels > 5) {
                freq_min += ((unsigned long)(r_rand()*625)) % channel_spacing;
	}
	debug("freq low=%lu high=%lu spacing=%lu\n", 
	       freq_min, freq_min+(num_fh_channels*channel_spacing), 
	       channel_spacing);

	// set the frequency and channel spacing
	// change base freq based on netid
	radio_set_frequency(freq_min, channel_spacing);

	// start on a channel chosen by network ID
	radio_set_channel(param_get(PARAM_NETID) % num_fh_channels);

	// And intilise the radio with them.
	if (!radio_configure(param_get(PARAM_AIR_SPEED)) &&
	    !radio_configure(param_get(PARAM_AIR_SPEED)) &&
	    !radio_configure(param_get(PARAM_AIR_SPEED))) {
		panic("radio_configure failed");
	}

	// report the real air data rate in parameters
	param_set(PARAM_AIR_SPEED, radio_air_rate());

	// setup network ID
	radio_set_network_id(param_get(PARAM_NETID));

	// setup transmit power
	radio_set_transmit_power(txpower);
	
	// report the real transmit power in settings
	param_set(PARAM_TXPOWER, radio_get_transmit_power());

#ifdef USE_RTC
	// initialise real time clock
	rtc_init();
#endif

	// initialise frequency hopping system
	fhop_init();

	// initialise TDM system
	tdm_init();
}
