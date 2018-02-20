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
int CurrentTemp1=0; 
int CurrentTemp2=0,CurrentTemp3=0,CurrentTemp4=0,CurrentTemp5=0,CurrentTemp6=0;

//unsigned char CharBuffer[21];
char CharBuffer[21];

//flags
unsigned char ErrFlag=0;
uint8_t Device1Presence=1,Device2Presence=1,Device3Presence=1,Device4Presence=1,Device5Presence=1,Device6Presence=1;

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
	int desatiny,cele;
	unsigned char i,chyba1=0,chyba2=0,chyba3=0,chyba4=0,chyba5=0,chyba6=0;
       
	   
	//DDRB |=(1<<PB3); //LED blink
	//PORTB|=(1<<PB3);
	// Port C initialization DS18b20 //
	DDRC &= ~(1 << PC0);   
    PORTC &= ~(1 << PC0);   
	DDRC &= ~(1 << PC1);   
    PORTC &= ~(1 << PC1);   
	DDRC &= ~(1 << PC2);   
    PORTC &= ~(1 << PC2);   
	DDRC &= ~(1 << PC3);   
    PORTC &= ~(1 << PC3);
	DDRD &= ~(1 << PD3);   
    PORTD &= ~(1 << PD3);   
	DDRD &= ~(1 << PD4);   
    PORTD &= ~(1 << PD4);   
	// enable interrupt
	sei();
	//deny interrupt
	//cli(); 
	//Watchdog initialization.
	wdt_reset();
	//wdt_enable(WDTO_8S); // for 5V supply,  At lower supply voltages, the times will increase 

	lcd_init( LCD_DISP_ON);
	 lcd_clrscr();
	 _delay_ms(80);
	
	 lcd_gotoxy( 1, 0);
	 lcd_puts_P( " modbus temp 0.1");
	 _delay_ms(1200);
	 lcd_gotoxy( 2, 1);		//column , row
	 lcd_puts_P( "kontrola snimacov");
	 lcd_gotoxy( 3, 2);		//column , row
	 lcd_puts_P( "DS18b20"); // msg0
	 _delay_ms(500);
	lcd_clrscr();

	lcd_gotoxy( 0, 0); // stlpec-riadok
	lcd_puts_P( "S1:");
	Device1Presence = ds18b20_reset(&PORTC,PC0);
	lcd_gotoxy( 4, 0);
	if(Device1Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 4, 0);lcd_puts_P( "----");chyba1=1;}
	_delay_ms(100);

	Device2Presence = ds18b20_reset(&PORTC,PC1);
	lcd_gotoxy( 0, 1);
	lcd_puts_P( "S2:");
	lcd_gotoxy( 4, 1);
	if(Device2Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 4, 1);lcd_puts_P( "----");chyba2=1;}
	_delay_ms(100);

	Device3Presence = ds18b20_reset(&PORTC,PC2);
	lcd_gotoxy( 0, 2);
	lcd_puts_P( "S3:");
	lcd_gotoxy( 4, 2);
	if(Device3Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 4, 1);lcd_puts_P( "----");chyba3=1;}
	_delay_ms(100);

	Device4Presence = ds18b20_reset(&PORTC,PC3);
	lcd_gotoxy( 0, 3);
	lcd_puts_P( "S4:");
	lcd_gotoxy( 4, 3);

	if(Device4Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 4, 3);lcd_puts_P( "----");chyba4=1;}

	_delay_ms(1000);

// ----------print ROM code----------------
	//chyba1=0;
	//chyba2=0;
	//chyba3=0;
	//chyba4=0;
//-----------------------------------------

	lcd_gotoxy( 0, 0);
	lcd_puts_P( "K1:");
	lcd_gotoxy( 3, 0);

	if(chyba1==0)
		{	read_ROM_CODE(&PORTC,PC0); 
			
		}
		else {
			lcd_puts_P( "----");
			}
	lcd_gotoxy( 0, 1);
	lcd_puts_P( "K2:");
	lcd_gotoxy( 3, 1);

	if(chyba2==0)
		{	read_ROM_CODE(&PORTC,PC1); 
			
		}
		else {
			lcd_puts_P( "----");
			}
	
	lcd_gotoxy( 0, 2);
	lcd_puts_P( "K3:");
	lcd_gotoxy( 3, 2);
	
	if(chyba3==0)
		{
			read_ROM_CODE(&PORTC,PC2);
		}
		else {
			lcd_puts_P( "----");
			}
	lcd_gotoxy( 0, 3);
	lcd_puts_P( "K4:");
	lcd_gotoxy( 3, 3);
	
	if(chyba4==0)
		{
			read_ROM_CODE(&PORTC,PC3);
		}
		else {
			lcd_puts_P( "----");
			}

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

	_delay_ms(500);
	lcd_clrscr();

	lcd_gotoxy( 0, 0);
	lcd_puts_P( "S1:");
	lcd_gotoxy( 0, 1);
	lcd_puts_P( "S2:");
	lcd_gotoxy( 0, 2);
	lcd_puts_P( "S3:");
	lcd_gotoxy( 0, 3);
	lcd_puts_P( "S4:");
	lcd_gotoxy( 11, 2);
	lcd_puts_P( "S5:");
	lcd_gotoxy( 11, 3);
	lcd_puts_P( "S6:");

//------------main loop-------------------------------------
	while(1)
 	{

	//while(1)
	//{
		//wdt_reset(); 
		
		if(chyba1==0)
		{
		CurrentTemp1 = ds18b20_gettemp(&PORTC,PC0); // decicelsius
		cele = CurrentTemp1/10;
		desatiny = ( CurrentTemp1 - (cele*10) );
		lcd_gotoxy( 3, 0);
		sprintf( CharBuffer, "%+i.%i\xC6\n",cele,desatiny);
		lcd_puts(CharBuffer);
		}
	//------------print user text------------------------------------
	
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
		//_delay_ms(200);
		
		if(chyba2==0)
		{
		CurrentTemp2 = ds18b20_gettemp(&PORTC,PC1);
		cele = CurrentTemp2/10;
		desatiny = (CurrentTemp2 - (cele*10) );
		sprintf( CharBuffer, "%+i.%i\xC6\n",cele,desatiny);
		//sprintf( CharBuffer, "%i \xC6\n",CurrentTemp2);
		lcd_gotoxy( 3, 1);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 9, 1);
		lcd_putc(0); // print user character on LCD
			
		_delay_ms(100);

		if(chyba3==0)
		{
		CurrentTemp3 = ds18b20_gettemp(&PORTC,PC2);
		cele = CurrentTemp3/10;
		desatiny = (CurrentTemp3 - (cele*10) );
		
		sprintf( CharBuffer, "%+i.%i\xC6\n",cele,desatiny);
		lcd_gotoxy( 3, 2);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 9, 2);
		lcd_putc(0); // print user character on LCD
			
		_delay_ms(100);

		if(chyba4==0)
		{
		CurrentTemp4 = ds18b20_gettemp(&PORTC,PC3);
		cele = CurrentTemp4/10;
		desatiny = (CurrentTemp4 - (cele*10) );
		sprintf( CharBuffer, "%+i.%i\xC6\n",cele,desatiny);
		lcd_gotoxy( 3, 3);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 9, 3);
		lcd_putc(0); // print user character on LCD
			
		_delay_ms(100);
		
		if(chyba4==0)
		{
		CurrentTemp4 = ds18b20_gettemp(&PORTC,PC3);
		cele = CurrentTemp4/10;
		desatiny = (CurrentTemp4 - (cele*10) );
		sprintf( CharBuffer, "%+i.%i\xC6\n",cele,desatiny);
		//sprintf( CharBuffer, "%i\xC6\n",CurrentTemp4);
		lcd_gotoxy( 14, 3);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 19, 3);
		lcd_putc(0); // print user character on LCD
			
		_delay_ms(100);


//get temperature BMP085
		d = bmp085_gettemperature();
		cele = d/10;
		desatiny = d - cele*10;
		sprintf( CharBuffer, "%+i.%i",cele,desatiny);
		//ltoa((d*10), printbuff, 10); // for long conversion function to string
		lcd_gotoxy( 14, 1);
		lcd_puts(CharBuffer);
		//lcd_puts( printbuff);
		lcd_putc(0); // print user character on LCD
		//dtostrf(d, 10, 2, printbuff);			// convert double to string
		//uart_puts("temperature: "); 
		//uart_puts(printbuff);  
		//uart_puts(" C deg"); 
		//uart_puts("\r\n");
		_delay_ms(200);

//get pressure BMP085
		l = bmp085_getpressure(gAltitudeCorr);			// in Pa
		//l = bmp085_getpressure(gAltitudeCorr*100); // in hPa 
		//ltoa(l, printbuff, 10);  				// convert long to string , for UART
		//uart_puts("rel.pressure:   "); 
		//uart_puts(printbuff);
		//uart_puts(" Pa");
		//uart_puts("\r\n");
		lcd_gotoxy( 17, 0);
		lcd_puts_P( "hPa");
		lcd_gotoxy( 13, 0);
		ltoa((l) , printbuff, 10); // in hPa (/100) in relative pressure to sea level, bmp085.h , for LCD
		lcd_puts( printbuff);
		
		
		_delay_ms(1000); 
		_delay_ms(7500);
		
		wdt_reset();

	}
		
}
