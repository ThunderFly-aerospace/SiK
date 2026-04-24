// -*- Mode: C; c-basic-offset: 8; -*-
//
// Copyright (c) 2012 Andrew Tridgell, All Rights Reserved
// Copyright (c) 2011 Michael Smith, All Rights Reserved
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
/// @file	tdm.c
///
/// one-way radio loop — the TDM state machine has been removed in the
/// `one_direction_2026` branch. Behaviour is decided once at boot from
/// the AT parameter RX_TX (S16):
///
///   RX_TX = 0 → receiver: listen on channel 0, push received bytes to
///               the serial port, emit a MAVLink RADIO report once a second.
///   RX_TX = 1 → transmitter: forward whatever arrives on the serial port
///               over the air in raw packets.
///
/// There is no hopping, no ACK, no window, no trailer, no duty cycle,
/// no LBT — the Si446x packet handler (preamble / sync / length / CRC16)
/// is the only framing on the air.
///

#include <stdarg.h>
#include "radio.h"
#include "tdm.h"
#include "timer.h"
#include "packet.h"
#include "serial.h"

/// shared packet buffer (also used by mavlink.c for report framing)
__xdata uint8_t pbuf[MAX_PACKET_LENGTH];

/// exported knobs from tdm.h — retained so parameters.c / main.c keep
/// linking. They have no effect in one-way mode.
__pdata uint8_t duty_cycle;
__pdata uint8_t lbt_rssi;

/// MAVLink framing state, owned by packet.c
extern uint8_t seen_mavlink;

/// AT command bookkeeping, owned by at.c
extern bool at_mode_active;

/// canary placed at 0xFF to detect stack overrun
__at(0xFF) uint8_t __idata _canary;

void
tdm_serial_loop(void)
{
	__pdata uint8_t  len;
	__pdata uint16_t tnow;
	__pdata uint16_t tlast_report;
	__pdata bool     is_tx;

	_canary = 42;

	is_tx = (param_get(PARAM_RX_TX) != 0);

	// fixed channel, no hopping
	radio_set_channel(0);

	if (!is_tx) {
		radio_receiver_on();
	}

	tlast_report        = timer2_tick();
	statistics.average_noise = 0;

	for (;;) {
		if (_canary != 42) {
			panic("stack blown\n");
		}

		if (pdata_canary != 0x41) {
			panic("pdata canary changed");
		}

		// let the AT command processor handle console input
		at_command();

		tnow = timer2_tick();

		if (!is_tx) {
			// --- receiver -----------------------------------
			if (!at_mode_active &&
			    ((uint16_t)(tnow - tlast_report) > 62500 /* ~1 s */)) {
				tlast_report  = tnow;
				seen_mavlink  = 2; // hardcoded MAVLink v2 report
				MAVLink_report();
				continue;
			}

			if (radio_receive_packet(&len, pbuf)) {
				statistics.average_rssi = (radio_last_rssi() +
				                           7 * (uint16_t)statistics.average_rssi) / 8;
				statistics.receive_count++;

				LED_ACTIVITY = LED_ON;
				serial_write_buf(pbuf, len);
				LED_ACTIVITY = LED_OFF;
			}
			continue;
		}

		// --- transmitter --------------------------------------
		len = packet_get_next(MAX_PACKET_LENGTH, pbuf);
		if (len != 0) {
			LED_ACTIVITY = LED_ON;
			radio_transmit(len, pbuf, 65000);
			LED_ACTIVITY = LED_OFF;
		}
	}
}

/// display local RSSI on demand (AT&T=RSSI, ATI7)
void
tdm_show_rssi(void)
{
	printf("RSSI: %u  noise: %u  pkts: %u",
	       (unsigned)statistics.average_rssi,
	       (unsigned)statistics.average_noise,
	       (unsigned)statistics.receive_count);
#ifdef INCLUDE_AES
	printf(" txe=%u rxe=%u stx=%u srx=%u crce=%u temp=%d\n",
#else
	printf(" txe=%u rxe=%u stx=%u srx=%u temp=%d\n",
#endif
	       (unsigned)errors.tx_errors,
	       (unsigned)errors.rx_errors,
	       (unsigned)errors.serial_tx_overflow,
	       (unsigned)errors.serial_rx_overflow,
#ifdef INCLUDE_AES
	       (unsigned)errors.crc_errors,
#endif
	       (int)radio_temperature());
	statistics.receive_count = 0;
}

/// one-line timing report (ATI6)
void
tdm_report_timing(void)
{
	printf("one-way mode, rx_tx=%u\n", (unsigned)param_get(PARAM_RX_TX));
}

/// remote AT command — not supported on a one-way link
void
tdm_remote_at(void)
{
}

/// TDM phase change — no TDM, nothing to do
void
tdm_change_phase(void)
{
}

void
tdm_init(void)
{
	// nothing timing-related to set up — keep the hook so main.c links
}
