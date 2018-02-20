/*
ds18b20 lib 0x02

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
modified 08-2017 by martin, used int as output
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ds18b20.h"

/*
 * ds18b20 init
 */
uint8_t ds18b20_reset() {
	uint8_t i;

	//low for 480us
	DS18B20_PORT &= ~ (1<<DS18B20_DQ); //low
	DS18B20_DDR |= (1<<DS18B20_DQ); //output
	_delay_us(480); //480

	//release line and wait for 60uS
	DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
	_delay_us(60); //60

	//get value and wait 420us
	i = (DS18B20_PIN & (1<<DS18B20_DQ));
	_delay_us(420); //420

	//return the read value, 0=ok, 1=error
	return i;
}

/*
 * write one bit
 */
void ds18b20_writebit(uint8_t bit){
	//low for 1uS
	DS18B20_PORT &= ~ (1<<DS18B20_DQ); //low
	DS18B20_DDR |= (1<<DS18B20_DQ); //output
	_delay_us(1);	//1

	//if we want to write 1, release the line (if not will keep low)
	if(bit)
		DS18B20_DDR &= ~(1<<DS18B20_DQ); //input

	//wait 60uS and release the line
	_delay_us(60);	//60
	DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
}

/*
 * read one bit
 */
uint8_t ds18b20_readbit(void){
	uint8_t bit=0;

	//low for 1uS
	DS18B20_PORT &= ~ (1<<DS18B20_DQ); //low
	DS18B20_DDR |= (1<<DS18B20_DQ); //output
	_delay_us(1);	//1

	//release line and wait for 14uS
	DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
	_delay_us(10);	//10

	//read the value
	if(DS18B20_PIN & (1<<DS18B20_DQ))
		bit=1;

	//wait 45uS and return read value
	_delay_us(53);	//53
	return bit;
}

/*
 * write one byte
 */
void ds18b20_writebyte(uint8_t byte){
	uint8_t i=8;
	while(i--){
		ds18b20_writebit(byte&1);
		byte >>= 1;
	}
}

/*
 * read one byte
 */
uint8_t ds18b20_readbyte(void){
	uint8_t i=8, n=0;
	while(i--){
		n >>= 1;
		n |= (ds18b20_readbit()<<7);
	}
	return n;
}

/*
 * get temperature
 */
//double ds18b20_gettemp() {  // before
  int16_t ds18b20_gettemp() {
	uint8_t temperature_l;
	uint8_t temperature_h;
	uint16_t teplota;
	uint8_t desatiny;
	//double retd = 0;
	uint8_t sign;
	int16_t retd = 5;

	#if DS18B20_STOPINTERRUPTONREAD == 1
	cli();
	#endif

	ds18b20_reset(); //reset
	ds18b20_writebyte(DS18B20_CMD_SKIPROM); //skip ROM
	ds18b20_writebyte(DS18B20_CMD_CONVERTTEMP); //start temperature conversion

	while(!ds18b20_readbit()); //wait until conversion is complete

	ds18b20_reset(); //reset
	ds18b20_writebyte(DS18B20_CMD_SKIPROM); //skip ROM
	ds18b20_writebyte(DS18B20_CMD_RSCRATCHPAD); //read scratchpad

	//read 2 byte from scratchpad
	temperature_l = ds18b20_readbyte();
	temperature_h = ds18b20_readbyte();
	sign = (temperature_h >> 4) & 0x0F;

	#if DS18B20_STOPINTERRUPTONREAD == 1
	sei();
	#endif
	
	if(sign == 0)
  	{
	teplota = (temperature_l & 0xF0) >> 4 | (temperature_h & 0x0F) << 4 ;   // signed teplota
	desatiny = (temperature_l & 0x0F) * 0.625;
  	retd = 10 * teplota;  
	retd = retd + desatiny;
	}
 else
    {
	temperature_l =~ temperature_l;
	temperature_h =~ temperature_h;
    teplota = (temperature_l & 0xF0) >> 4 | (temperature_h & 0x0F) << 4 ;   // signed teplota
    desatiny = ((temperature_l + 1) & 0x0F) * 0.625;
    retd = (teplota*10+desatiny)*(-1);
	}

//************** test LED************
//PORTB |= (1 << PB5); // set high
PORTB ^= (1 << PB5);	// set toggle
//_delay_ms(600);
//PORTB &= ~(1 << PB5); // set low
//_delay_ms(500);

	return retd; // output in decicelsius *10
}

