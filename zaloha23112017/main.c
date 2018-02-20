//
//
// fuses set for Atmega328P L-C6, H-DD
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
//-------------
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
//-----------------
#include "lcd.h"
#include "ds18b20.h"

//current temperatures
int16_t CurrentTemp1=0; 
int CurrentTemp2=0;

//unsigned char CharBuffer[21];
char CharBuffer[21];

//flags
unsigned char ErrFlag=0;
uint8_t Device1Presence=1,Device2Presence=1;

//user char
	static const PROGMEM unsigned char userChar[] =
	{
	0x18, 0x18, 0x06, 0x09, 0x08, 0x08, 0x09, 0x06,
	0x07, 0x08, 0x13, 0x14, 0x14, 0x13, 0x08, 0x07,
	0x00, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x00
	};

int main(void)
{
	
	unsigned char i;
       
	   
	//DDRB |=(1<<PB3); //LED blink
	//PORTB|=(1<<PB3);
	// Port C initialization DS18b20 //
	DDRC &= ~(1 << PC0);   
    PORTC &= ~(1 << PC0);   
	DDRC &= ~(1 << PC3);   
    PORTC &= ~(1 << PC3);
	// enable interrupt
	//sei();
	//deny interrupt
	cli(); 
	//Watchdog initialization.
	wdt_reset();
	wdt_enable(WDTO_8S); 

	lcd_init( LCD_DISP_ON);
	 lcd_clrscr();
	 _delay_ms(80);
	
	 lcd_gotoxy( 1, 0);
	 lcd_puts_P( " modbus temp 0.1");
	 //_delay_ms(100);
	 lcd_gotoxy( 2, 1);		//column , row
	 lcd_puts_P( "kontrola snimacov");
	 lcd_gotoxy( 3, 2);		//column , row
	 lcd_puts_P( "DS18b20"); // msg0
	 _delay_ms(500);
	lcd_clrscr();

	lcd_gotoxy( 0, 0);
	lcd_puts_P( "Kanal 1:");
	Device1Presence = ds18b20_reset(&PORTC,PC0);
	lcd_gotoxy( 9, 0);
	if(Device1Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 14, 0);lcd_puts_P( "chyba");}
	_delay_ms(500);

	Device2Presence = ds18b20_reset(&PORTC,PC3);
	lcd_gotoxy( 0, 1);
	lcd_puts_P( "Kanal 2:");
	lcd_gotoxy( 9, 1);
	if(Device2Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 14, 1);lcd_puts_P( "chyba");}

	lcd_gotoxy( 0, 2);
	read_ROM_CODE(&PORTC,PC0); // print ROM code
	lcd_gotoxy( 0, 3);
	read_ROM_CODE(&PORTC,PC3);

	_delay_ms(1500);
	_delay_ms(1500);

	while(1)
 	{

	//while(1)
	//{
		//wdt_reset(); 
		CurrentTemp1 = ds18b20_gettemp(&PORTC,PC0); // decicelsius 
		lcd_gotoxy( 8, 0);
		sprintf( CharBuffer, "%i \xC6\n",CurrentTemp1);
		lcd_puts(CharBuffer);
	//------------------------------------------------
		/*
        * load two userdefined characters from program memory
        * into LCD controller CG RAM location 0 and 1
        */
       lcd_command(_BV(LCD_CGRAM));  /* set CG RAM start address 0 */
       for(i=0; i<24; i++)
       {
          lcd_data(pgm_read_byte_near(&userChar[i]));
       }
		lcd_gotoxy( 13, 0);
		lcd_putc(0); // print user character on LCD
		//lcd_putc(1);
		//lcd_putc(2);
	//----------------------------------------------------	
		/*
		lcd_text("vonku:");		// uzivatelsky vypis
		gotoxy(1,12);			// kurzor pre vypis teploty na displej 
		lcd_char(cele);         // vypis na disp v tvare XX.X-C
		lcd_text(".");
		lcd_char(desatine);
		lcd_char(0b10110010);   // funkcia vypis char
		lcd_text("C");

		*/	
		_delay_ms(200);
		
		
		CurrentTemp2 = ds18b20_gettemp(&PORTC,PC3);
		//lcd_puts_P( "ide§");
		sprintf( CharBuffer, "%i \xC6\n",CurrentTemp2);
		lcd_gotoxy( 8, 1);
		lcd_puts(CharBuffer);
			
		_delay_ms(500);
		_delay_ms(500);
		wdt_reset();

	}
		
}
