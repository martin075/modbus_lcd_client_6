
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000UL
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

unsigned char CharBuffer[8];
//flags
unsigned char ErrFlag=0;
unsigned char Device1Presence,Device2Presence;

int main(void)
{
	DDRB |=(1<<PB3); //enable backlight
	PORTB|=(1<<PB3);
	LCD_Initialize();
	LCD_DisplayString(PSTR("Sprawdznie"));
	LCD_LocateXY(0,1);
	LCD_DisplayString(PSTR("czujnikow..."));


	Device1Presence=OW_Reset(&PORTB,PB0);
	LCD_ClearScreen();
	LCD_DisplayString(PSTR("Kanal 1:"));
	LCD_LocateXY(0,1);
	if(Device1Presence)
			LCD_DisplayString(PSTR("OK"));
	else LCD_DisplayString(PSTR("Brak czujnika"));
	_delay_ms(1000);

	Device2Presence=OW_Reset(&PORTB,PB2);
	LCD_ClearScreen();
	LCD_DisplayString(PSTR("Kanal 2:"));
	LCD_LocateXY(0,1);
	if(Device2Presence)
			LCD_DisplayString(PSTR("OK"));
	else LCD_DisplayString(PSTR("Brak czujnika"));
	_delay_ms(1000);
	
	if(Device1Presence)
		OW_Initialization(&PORTB,PB0);
	if(Device2Presence)
		OW_Initialization(&PORTB,PB1);

	while(1)
	{
		CurrentTemp1=OW_GetRawTemperature(ErrFlag,&PORTB,PB0);
		OW_FormatRawTemperature(CharBuffer,CurrentTemp1,2);
		LCD_LocateXY(0,0);
		LCD_DisplayRamString(CharBuffer);	
		_delay_ms(500);
		CurrentTemp1=OW_GetRawTemperature(ErrFlag,&PORTB,PB2);
		OW_FormatRawTemperature(CharBuffer,CurrentTemp2,2);
		LCD_LocateXY(0,1);
		LCD_DisplayRamString(CharBuffer);
		_delay_ms(500);
		_delay_ms(500);

	}
		
}
