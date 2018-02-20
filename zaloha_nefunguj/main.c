//
//
// fuses set for Atmega328P L-C6, H-DD

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
//#define F_CPU 16000000UL //defined in AS
#include <util/delay.h>
#include <string.h>
//-------------
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "hd4478.h"
#include "onewire.h"

//current temperatures
int CurrentTemp1=0;
int CurrentTemp2=0;

unsigned char CharBuffer[21];
//flags
unsigned char ErrFlag=0;
unsigned char Device1Presence,Device2Presence;

int main(void)
{
	
	LCD_Initialize();

	//lcd_init( LCD_DISP_ON);
//	 lcd_clrscr();
	 _delay_ms(80);
	 LCD_LocateXY(0,1);
	
	//DDRB |=(1<<PB3); //LED blink
	//PORTB &= ~(1 << PB3); // set low
	//_delay_ms(1000);
	//PORTB|=(1<<PB3);
	

//	 lcd_gotoxy( 0, 0);
	 //lcd_puts_P( " modbus temp 0.1");
	 LCD_DisplayString(PSTR("6xDS18b20"));
	 _delay_ms(500);
	 //lcd_gotoxy( 0, 1);		//column , row
	 LCD_LocateXY(0,1);
	 //lcd_puts_P( " kontrola ");
	 LCD_DisplayString(PSTR("kontrola"));
	 LCD_LocateXY(0,2);
	 //lcd_gotoxy( 0, 2);		//column , row
	 //sprintf( lcd_buff, msg0);
	 LCD_DisplayString(PSTR("snimacov"));
	 //lcd_puts_P( "snimacov"); // msg0
		//	 sprintf( lcd_buff, "%4is", msg0);
	 //lcd_puts( lcd_buff);
  	 //lcd_gotoxy( 0, 3); 
	
		/*	LCD_Initialize();
			LCD_DisplayString(PSTR("kontrola"));
			LCD_LocateXY(0,1);
			LCD_DisplayString(PSTR("snimacov..."));
			LCD_ClearScreen();
			LCD_DisplayString(PSTR("Kanal 1:"));
			LCD_LocateXY(0,1);
			*/
	LCD_ClearScreen();
	//lcd_clrscr();
	//lcd_gotoxy( 0, 0);
	LCD_DisplayString(PSTR("Kanal 1:"));

//	lcd_puts_P( "Kanal 1:");
	Device1Presence=OW_Reset(&PORTD,PD6);
	//lcd_gotoxy( 9, 0);
	LCD_LocateXY(9,0);

	if(Device1Presence)
			LCD_DisplayString(PSTR("OK"));
			//lcd_puts_P( "OK");
		//else {  lcd_gotoxy( 14, 0);lcd_puts_P( "chyba");}
		else {  LCD_LocateXY( 14, 0);LCD_DisplayString(PSTR("chyba"));}
	_delay_ms(1000);

	Device2Presence=OW_Reset(&PORTC,PC3);
	//lcd_gotoxy( 0, 1);
	LCD_LocateXY(0,1);
	//lcd_puts_P( "Kanal 2:");
	LCD_DisplayString(PSTR("Kanal 2:"));
	LCD_LocateXY(9,1);
	//lcd_gotoxy( 9, 1);
	if(Device2Presence)
			//lcd_puts_P( "OK");
			LCD_DisplayString(PSTR("OK"));
		else {  LCD_LocateXY( 14, 1);LCD_DisplayString(PSTR("chyba"));}
		//else {  lcd_gotoxy( 14, 1);lcd_puts_P( "chyba");}
		
	_delay_ms(1000);
	
	if(Device1Presence)
		OW_Initialization(&PORTD,PD6);
	if(Device2Presence)
		OW_Initialization(&PORTC,PC3);

	while(1)
	{
		CurrentTemp1=OW_GetRawTemperature(ErrFlag,&PORTD,PD6);
		OW_FormatRawTemperature(CharBuffer,CurrentTemp1,1);
		LCD_LocateXY(8,0);
		//lcd_gotoxy( 8, 0);

		LCD_DisplayRamString(CharBuffer);
		//sprintf( gBuffer, "%i#Out %+04i.%c\xC6\n",(int)page, gReadings[device] / 10,(gReadings[device] % 10) + '0');
		//	lcd_puts( gBuffer);
		//lcd_puts(CharBuffer);	
		_delay_ms(500);
		
		CurrentTemp1=OW_GetRawTemperature(ErrFlag,&PORTC,PC3);
		OW_FormatRawTemperature(CharBuffer,CurrentTemp2,1);
		//lcd_gotoxy( 8, 1);
		LCD_LocateXY(8,1);
		//lcd_puts(CharBuffer);
		LCD_DisplayRamString(CharBuffer);
		_delay_ms(500);
		_delay_ms(500);

	}
		
}
