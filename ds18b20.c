/*
ds18b20 lib
based on lib by Davide Gironi, 2012
Released under GPLv3.
Please refer to LICENSE file for licensing information.
without CRC check
modified 08-2017 by martin, used int as output, 12 bit resolution,...
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ds18b20.h"
#include "lcd.h"
/*
 * ds18b20 init
 */
uint8_t ds18b20_reset(volatile unsigned char *Port, unsigned char Pin) 
{
	uint8_t i=0,j=0; // i- presence pulse, j- bus release

	
	//low for 480us
	*Port &= ~(1<<Pin); // pin low
	*(Port-1)|=(1<<Pin);  //pin as output
	_delay_us(500); //480

	//release line and wait for 60uS
	*(Port-1) &= ~(1<<Pin); //pin as input without pullup
	_delay_us(60); //60

	//get value and wait 420us
	
	if((*(Port-2))&(1<<Pin)) {i = 0;} else {i = 1;}
	_delay_us(250); //device after 15-60us pull down line for 60-240us
	if((*(Port-2))&(1<<Pin)) {j = 1;} else {j = 0;}
	//return presence bit(0-no device,1-device OK)

	return (i & j);
}

/*
 * write one bit
 */
void ds18b20_writebit(volatile unsigned char *Port, unsigned char Pin, uint8_t bit)
{
	//low for 1uS
	*Port &= ~ (1<<Pin);
	 //output
	*(Port-1)|=(1<<Pin);
	_delay_us(1);	//1uS
	//if we want to write 1, release the line (if not will keep low)
	if(bit)
		*(Port-1) &= ~ (1<<Pin);  //input
	//wait 60uS and release the line
	_delay_us(60);	//60
	*(Port-1) &= ~ (1<<Pin); //input
}

/*
 * read one bit
 */
uint8_t ds18b20_readbit(volatile unsigned char *Port, unsigned char Pin)
{
	uint8_t bit=0;

	//low for 1uS
	//low
	*Port &= ~(1<<Pin);
	 //output
	*(Port-1) |= (1<<Pin);
	_delay_us(1);	//1

	//release line and wait for 14uS
	//input
	*(Port-1) &= ~(1<<Pin);
	_delay_us(14);	//10

	//read the value
	if( (*(Port-2)) & (1<<Pin) )
		bit=1;

	//wait 45uS and return read value
	_delay_us(53);	//53
	return bit;
}

/*
 * write one byte
 */
void ds18b20_writebyte(volatile unsigned char *Port, unsigned char Pin, uint8_t byte)
{
	uint8_t i=8;
	while(i--){
		ds18b20_writebit(Port, Pin, byte&1);
		byte >>= 1;
	}
}



/*
 * read one byte
 */
uint8_t ds18b20_readbyte(volatile unsigned char *Port, unsigned char Pin)
{
	uint8_t i=8, n=0;
	while(i--){
		n >>= 1;
		n |= (ds18b20_readbit(Port, Pin)<<7);
	}
	return n;
}

/*
	* read ROM code from sensor, and print it on LCD on actual position
*/

void read_ROM_CODE(volatile unsigned char *Port, unsigned char Pin)
{
	volatile unsigned char ROM_code[8];
	unsigned i,j;
	cli(); // disable interrupts
	ds18b20_reset(Port, Pin); //reset OW bus
	/*
	for(i=0;i<8;i++)
	{
		*(Port-1) |= (1<<Pin); //pin as output
		*Port &= ~(1<<Pin); //DQ low
		_delay_us(2);
		*(Port-1) &= ~(1<<Pin); //pin as in
		_delay_us(10);
		ROM_code |= (((*(Port-2))&(1<<Pin))<<i);	//collect data
		_delay_us(60);
	}
	//return(ROM_code);
	*/


	ds18b20_writebyte(Port, Pin, DS18B20_CMD_READROM); //read ROM
	for(i=0;i<8;i++)
	{
		ROM_code[i] = ds18b20_readbyte(Port, Pin);
	}
	//sei(); // enable interrupts
	
	for(j=0;j<8;j++)
	{
		lcd_puthex_byte(ROM_code[j]);
	}
}


/*
 * get temperature
 */
int16_t ds18b20_gettemp(volatile unsigned char *Port, unsigned char Pin)
{
	uint8_t temperature_l;
	uint8_t temperature_h;
	uint16_t teplota;
	uint8_t desatiny;
	//double retd = 0;
	uint8_t sign;
	int16_t retd = 5;

	//#if DS18B20_STOPINTERRUPTONREAD == 1
	//cli(); //interrupt deny 
	//#endif

	ds18b20_reset(Port, Pin); //reset
	ds18b20_writebyte(Port, Pin, DS18B20_CMD_SKIPROM); //skip ROM
	ds18b20_writebyte(Port, Pin, DS18B20_CMD_CONVERTTEMP); //start temperature conversion

	while(!ds18b20_readbit(Port, Pin)); //wait until conversion is complete

	ds18b20_reset(Port, Pin); //reset
	ds18b20_writebyte(Port, Pin, DS18B20_CMD_SKIPROM); //skip ROM
	ds18b20_writebyte(Port, Pin, DS18B20_CMD_RSCRATCHPAD); //read scratchpad

	//read 2 byte from scratchpad
	temperature_l = ds18b20_readbyte(Port, Pin);
	temperature_h = ds18b20_readbyte(Port, Pin);
	sign = (temperature_h >> 4) & 0x0F;

	//#if DS18B20_STOPINTERRUPTONREAD == 1
	//sei();  //interrupt allow
	//#endif
	
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
	sei();
	
//******************* flash LED ******************
// command 
//PORTB &= ~(1 << PB5); // set low
//_delay_ms(600);
//PORTB |= (1 << PB5); // set high
//_delay_ms(200);
//************************************************

	return retd; // output in decicelsius *10
}

