// ivan orfanidi c avr tests programs - from github
// Atmega48,atmega328P (16MHz) 
//PB0, PB1 - config of baudrate
//PB3 - slave ID
// port DDRD - RE enable
// PC0 - wired 18b20
// lib 18b20 - modified Davide Gironi lib
//****************************************************
//Functions Device.
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <avr/eeprom.h>
	#include <avr/wdt.h>
	#include <avr/pgmspace.h>

// Standard Input/Output functions.
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <math.h>

	#include "USART.h"
	#include "MODBUS_SLAVE.h"
	#include "DS18B20.h"

	#define PIN_BAUDRATE 		PINB
	#define BAUDRATE0 			(1<<PB0)
	#define BAUDRATE1 			(1<<PB1)

	#define RESET_SLAVE_ID		(1<<PB3)
	#define SLAVE_ADD			0xA

	uint8_t back_len0 = 0;
	uint8_t slave_add;
	uint32_t convert_delay=0;	
	uint16_t celsiusTemperature = 99;    		//new- The temperature read from the DS18b20 in decicelsius
	
	#define ADDR_SLAVE_ID_MODBUS_EEP	0x0000 //0x0000

	#define TIME_UPDATE					100000 // in ms


void init(void)
{
	// Port B initialization //
	// first DDRB, next PORTB
	//DDRB |= _BV(PB5) or means the same DDRB |=(1<<PB5)
	DDRB &= ~(BAUDRATE0) | (BAUDRATE1) | (RESET_SLAVE_ID);	//set as Input
	DDRB |= (1 << PB5); // output - for blinking led
	//DDRB = 0x00; // input - setting baud...

	PORTB = BAUDRATE0 | BAUDRATE1 | RESET_SLAVE_ID;
	
		
	// Port D initialization RE enable//

	DDRD = (1<<PD2);
	PORTD = 0x00;

	// Port C initialization DS18b20 //

	//DDRC =  (1<<PC0);
	//PORTC = 0x00;
	DDRC &= ~(1 << PC0);   
    PORTC &= ~(1 << PC0);  

	//Analog Comparator initialization.

	ACSR|=(1<<ACD);		//Disable Comparator.



	///Timer1 initialization.

	OCR1A=250; //300


	TIMSK1|=(1<<OCIE1A);

	//////////////////////////////////////////////


	//Init Timer0//



	/////////////////////////////////////////////////////////////////////

	//Watchdog initialization.
	wdt_reset();								
	wdt_enable(WDTO_8S);


}

/////////////////////////////////////////////////////////////////////

uint8_t select_baud_rate(void)
{
	uint8_t baud_rate = 1;

	uint8_t pin_baud_rate = PIN_BAUDRATE;

	pin_baud_rate &= 0b00000011;

	switch(pin_baud_rate)
	{
		case 3:
			baud_rate = 1;	//Baudrate 2400.
			break;

		case 2:
			baud_rate = 2;	//Baudrate 4800.
			break;

		case 1:
			baud_rate = 3;	//Baudrate 9600.
			break;

		case 0:
			baud_rate = 5;	//Baudrate 19200.
			break;
	}

	return baud_rate; 
}


/////////////////////////////////////////////////////////////////////

void reset_slave_id(void)
{
	eeprom_update_word((uint16_t*)ADDR_SLAVE_ID_MODBUS_EEP, 0x0001);

	while(1)
		wdt_reset();
}


/////////////////////////////////////////////////////////////////////





int main(void)
{
	init();

	if(!(PIN_BAUDRATE & RESET_SLAVE_ID)) reset_slave_id();
	
	registers[7]=eeprom_read_word((uint16_t*)ADDR_SLAVE_ID_MODBUS_EEP);
		
	if(registers[7]==0xFFFF)
	{
		registers[7]=0x0001;
		eeprom_update_word((uint16_t*)ADDR_SLAVE_ID_MODBUS_EEP, registers[7]);
	}

		//slave_add=eeprom_read_byte((uint8_t*)ADDR_SLAVE_ID_MODBUS_EEP);
	slave_add= SLAVE_ADD; // for testing
	usart0_mod_init(select_baud_rate());

	sei();						//Enable Interrupt.


	while(1)
	{
		wdt_reset();

		if(convert_delay==1)
		{
			celsiusTemperature = ds18b20_gettemp(); // decicelsius
			registers[8]=celsiusTemperature; 
			//registers[9]=(Temperature[1]<<8)|(Temperature[2]);
			//registers[10]=Temperature[3];

			_delay_ms(500); // delay for loop
		}

		
		if(convert_delay==0)
		{
			
			if(ds18b20_reset())
			{
				for(uint8_t i=8; i<11; i++)
					registers[i]=0x9292; // not valid value

				convert_delay=1;
			}
				else
				{
					convert_delay = TIME_UPDATE;
				}	
		}


		convert_delay--;
	
		//settings of protokol modbus
		if(usart0_rx_len()!=back_len0)	
			{
			back_len0=usart0_rx_len();
			TCNT1=0x0000; 
			TCCR1B=(1<<CS12)|(0<<CS11)|(0<<CS10);
			}
		

	}

}

/// INTERRUPT ///

// prepare of modbus
ISR(TIMER1_COMPA_vect)
{

	TCCR1B=(0<<CS12)|(0<<CS11)|(0<<CS10);

	TCNT1=0x0000;

	back_len0=0;

	sei();

	if(!(modbus_slave(slave_add)))  // 0- ok, 1 - not slave add,...
	{
		eeprom_update_word((uint16_t*)ADDR_SLAVE_ID_MODBUS_EEP, registers[7]);
	}

}


//Interrupt Watchdog Timer//
ISR(WDT_vect)
{

}



