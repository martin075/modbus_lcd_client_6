
#ifndef MODBUS_SLAVE_H
   #define MODBUS_SLAVE_H

// Standard Input/Output functions.
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <avr/io.h>
	#include <util/delay.h>
	#include <util/crc16.h>

	#include "USART.h"

	#define COMMAND_HOLDING_REG	 3 // read analog output register
	#define COMMAND_INPUT_REG	 4 // read analog input register
	#define COMMAND_WRITE_REG	 16 // write multiple analog output holding register

	#define PORT_RS485 PORTD	//!
	#define RE_DE PD2			//control pin for RS485 - RE_DE!
	#define USART_MODBUS 0		//number of port for modbus мНЛЕП ОНПРЮ ОН ЛНДАЮЯС.

	#define ADDRES_REG_READ 	7	// first address of modbus registers мювюкэмши юдпея пецхярпнб времхъ //
	#define QUANTITY_REG_READ 	4	// qauntity of reading registers йнкхвеярбн пецхярпнб времхъ //

	#define ADDRES_REG_WRITE 	7	// first address of writing register мювюкэмши юдпея пецхярпнб гюохях //
	#define QUANTITY_REG_WRITE 	1	// quantity of writing register йнкхвеярбн пецхярпнб гюохях //

	#define ADDRES_REG		 	7
	#define QUANTITY_REG 		4
	
	
	int16_t registers[ADDRES_REG+QUANTITY_REG];	//communication throw наыемхе c main вепег щрнр люяхб!!!//


	int modbus_slave(uint8_t slave_add); // 0-OK; 1-NOT SLAVE ADDRESS; 2-ERROR; 3-ERROR CRC;//

enum {
	OK=0, NOT_SLAVE_ID, ERROR_ADDR_REG, ERROR_FUNCTION, ERROR_CRC
};

#endif
