/*
ds18b20 lib 0x02

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.

References:
  + Using DS18B20 digital temperature sensor on AVR microcontrollers
    by Gerard Marull Paretas, 2007
    http://teslabs.com/openplayer/docs/docs/other/ds18b20_pre1.pdf
*/


#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>

//setup connection
#define 1DS18B20_PORT PORTC
#define 1DS18B20_DDR DDRC
#define 1DS18B20_PIN PINC
#define 1DS18B20_DQ PC0

#define 2DS18B20_PORT PORTC
#define 2DS18B20_DDR DDRC
#define 2DS18B20_PIN PINC
#define 2DS18B20_DQ PC1

#define 3DS18B20_PORT PORTC
#define 3DS18B20_DDR DDRC
#define 3DS18B20_PIN PINC
#define 3DS18B20_DQ PC2

#define 6DS18B20_PORT PORTC
#define 6DS18B20_DDR DDRC
#define 6DS18B20_PIN PINC
#define 6DS18B20_DQ PC3

#define 4DS18B20_PORT PORTD
#define 4DS18B20_DDR DDRD
#define 4DS18B20_PIN PIND
#define 4DS18B20_DQ PD3

#define 5DS18B20_PORT PORTD
#define 5DS18B20_DDR DDRD
#define 5DS18B20_PIN PIND
#define 5DS18B20_DQ PD4

//commands
#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe
#define DS18B20_CMD_WSCRATCHPAD 0x4e
#define DS18B20_CMD_CPYSCRATCHPAD 0x48
#define DS18B20_CMD_RECEEPROM 0xb8
#define DS18B20_CMD_RPWRSUPPLY 0xb4
#define DS18B20_CMD_SEARCHROM 0xf0
#define DS18B20_CMD_READROM 0x33
#define DS18B20_CMD_MATCHROM 0x55
#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_ALARMSEARCH 0xec

//stop any interrupt on read
#define DS18B20_STOPINTERRUPTONREAD 0

//functions
//extern double ds18b20_gettemp();  //before
int16_t ds18b20_gettemp();

#endif
