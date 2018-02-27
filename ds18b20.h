<<<<<<< HEAD
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
int16_t ds18b20_gettemp(volatile unsigned char *Port, unsigned char Pin);
uint8_t ds18b20_reset(volatile unsigned char *Port, unsigned char Pin);
void ds18b20_writebit(volatile unsigned char *Port, unsigned char Pin, uint8_t bit);
uint8_t ds18b20_readbit(volatile unsigned char *Port, unsigned char Pin);
void ds18b20_writebyte(volatile unsigned char *Port, unsigned char Pin, uint8_t byte);
uint8_t ds18b20_readbyte(volatile unsigned char *Port, unsigned char Pin);
void read_ROM_CODE(volatile unsigned char *Port, unsigned char Pin);

#endif
=======
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
int16_t ds18b20_gettemp(volatile unsigned char *Port, unsigned char Pin);
uint8_t ds18b20_reset(volatile unsigned char *Port, unsigned char Pin);
void ds18b20_writebit(volatile unsigned char *Port, unsigned char Pin, uint8_t bit);
uint8_t ds18b20_readbit(volatile unsigned char *Port, unsigned char Pin);
void ds18b20_writebyte(volatile unsigned char *Port, unsigned char Pin, uint8_t byte);
uint8_t ds18b20_readbyte(volatile unsigned char *Port, unsigned char Pin);
void read_ROM_CODE(volatile unsigned char *Port, unsigned char Pin);

#endif
>>>>>>> origin/master
