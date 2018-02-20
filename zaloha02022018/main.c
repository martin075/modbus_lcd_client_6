// DS18B20 - +-0,5°C
// BMP180 - +-1°C, -4 +2 hPa
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
#include "bmp085.h"

#define MODE_altitude 7			// altitude correction for relative barometric pressure

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
//--------for bmp085----------------
int32_t gAltitudeCorr; // altitude correction for relative barometric pressure
long l;
double d;
//float d; // in gcc float and double has the same 4B
char printbuff[10];

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
	lcd_puts_P( "S1:");
	Device1Presence = ds18b20_reset(&PORTC,PC0);
	lcd_gotoxy( 5, 0);
	if(Device1Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 14, 0);lcd_puts_P( "chyba");}
	_delay_ms(500);

	Device2Presence = ds18b20_reset(&PORTC,PC3);
	lcd_gotoxy( 0, 1);
	lcd_puts_P( "S2:");
	lcd_gotoxy( 5, 1);
	if(Device2Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 14, 1);lcd_puts_P( "chyba");}
// ----------print ROM code----------------
	lcd_gotoxy( 0, 2);
	lcd_puts_P( "K1:");
	lcd_gotoxy( 3, 2);
	read_ROM_CODE(&PORTC,PC0); 
	lcd_gotoxy( 0, 3);
	lcd_puts_P( "K2:");
	lcd_gotoxy( 3, 3);
	read_ROM_CODE(&PORTC,PC3);

		/*
        * load two userdefined characters from program memory
        * into LCD controller CG RAM location 0 and 1
        */
       lcd_command(_BV(LCD_CGRAM));  /* set CG RAM start address 0 */
       for(i=0; i<24; i++)
       {
          lcd_data(pgm_read_byte_near(&userChar[i]));
       }

// set up bmp085board
	bmp085_init();

	_delay_ms(1500);
	_delay_ms(1500);

//------------main loop-------------------------------------
	while(1)
 	{

	//while(1)
	//{
		//wdt_reset(); 
		CurrentTemp1 = ds18b20_gettemp(&PORTC,PC0); // decicelsius 
		lcd_gotoxy( 4, 0);
		sprintf( CharBuffer, "%i \xC6\n",CurrentTemp1);
		lcd_puts(CharBuffer);
	//------------------------------------------------
	
		lcd_gotoxy( 9, 0);
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
		lcd_gotoxy( 4, 1);
		lcd_puts(CharBuffer);
		lcd_gotoxy( 9, 1);
		lcd_putc(0); // print user character on LCD
			
		_delay_ms(1000); // musia byt rozne pri 1500 a 1500 sa mi to samo resetuje
		_delay_ms(1500);

//get temperature BMP085
		d = bmp085_gettemperature();
		ltoa((d*10), printbuff, 10); // for long conversion function to string
		lcd_gotoxy( 13, 0);
		lcd_puts( printbuff);
		lcd_putc(0); // print user character on LCD
		//dtostrf(d, 10, 2, printbuff);			// convert double to string
		//uart_puts("temperature: "); 
		//uart_puts(printbuff);  
		//uart_puts(" C deg"); 
		//uart_puts("\r\n");

//get pressure BMP085
		l = bmp085_getpressure(gAltitudeCorr);			// in Pa
		//l = bmp085_getpressure(gAltitudeCorr*100); // in hPa 
		//ltoa(l, printbuff, 10);  				// convert long to string , for UART
		//uart_puts("rel.pressure:   "); 
		//uart_puts(printbuff);
		//uart_puts(" Pa");
		//uart_puts("\r\n");
		lcd_gotoxy( 17, 1);
		lcd_puts_P( "hPa");
		lcd_gotoxy( 13, 1);
		ltoa((l) , printbuff, 10); // in hPa (/100) in relative pressure to sea level, bmp085.h , for LCD
		lcd_puts( printbuff);

		wdt_reset();

	}
		
}
