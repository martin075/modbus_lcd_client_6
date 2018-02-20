
#ifndef USART_H
   #define USART_H

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include <ctype.h>
#include <util/delay.h>

	#define RX_BUFFER_SIZE0 128
	#define TX_BUFFER_SIZE0 128

	#define BAUD_RATE0 9600
	#define u2x0		0
	#define CHARTER_SIZE0 8
	#define PARITY_MODE0 'N'
	#define STOP_BIT0	1


	#define RX_BUFFER_SIZE1 256
	#define TX_BUFFER_SIZE1 256

	#define BAUD_RATE1 19200
	#define u2x1		0
	#define CHARTER_SIZE1 8
	#define PARITY_MODE1 'N'
	#define STOP_BIT1	1

	#define USART0_DELAY_MS 5
	#define USART1_DELAY_MS 0

	#define UPE0 2
	#define DOR0 3
	#define FE0 4


	uint8_t rx_status0;
	uint8_t tx_status0;

	void usart0_init();

	void usart0_mod_init(uint8_t baud_rate);

	void usart0_clear_tx_buffer();

	void usart0_clear_rx_buffer();

	void usart0_write(uint8_t byte);

	void usart0_write_str(char *pData_Usart0);

	uint8_t usart0_read();

	uint8_t usart0_rx_len();

	uint8_t rx_error0();

	uint8_t usart0_busy_wait(void);

	void usart_init0();

	#if defined (__AVR_ATmega162__) || (__AVR_ATmega128__)

		uint8_t rx_status1;
		uint8_t tx_status1;

		void usart1_init();

		void usart1_mod_init(uint8_t baud_rate);

		void usart1_clear_tx_buffer();

		void usart1_clear_rx_buffer();

		void usart1_write(uint8_t byte);

		uint8_t usart1_read();

		uint8_t usart1_rx_len();

		uint8_t rx_error1();

		uint8_t usart1_busy_wait(void);

		void usart_init1();

		void usart1_write_str(char *pData_Usart1);

	#endif

#endif
