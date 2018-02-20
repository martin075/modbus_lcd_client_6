/*
************************************************************************  
  Filename	 	-  hd4478.c
  Author 		-  BESEA Robotics
  Data 			-  20-10-2008
  Processor 	-  Atmel ATmega32/16/8 and similar
  Description	: 
  HD4478 driver based display library.
  
  
  User definined:
			Communication
  
  Licencja - GPL 
  Ostania modyfikacja  - 
************************************************************************ 
*/

#include "hd4478.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>


void LCD_E(unsigned char ucE)
{
	//set enable (rise strobe)
	if(ucE !=0)
		CONTROLPORT |= (1<<LCD_PIN_E);
	//clear enable(fall strobe)
	else
		CONTROLPORT &= ~(1<<LCD_PIN_E);
}

void LCD_RS(unsigned char ucRS)
{
	//set RS
	if(ucRS !=0)
		CONTROLPORT_RS |= (1<<LCD_PIN_RS);
	//clear RS
	else
		CONTROLPORT_RS &= ~(1<<LCD_PIN_RS);
}

//function divide byte to two half-bytes and send it to lcd display
void LCD_SendByte(unsigned char ucByte)
{
	LCD_E(1);
	//clear data IO pins
	DATAPORT &= ~(1<<LCD_PIN_DB4);
	DATAPORT &= ~(1<<LCD_PIN_DB5);
	DATAPORT &= ~(1<<LCD_PIN_DB6);
	DATAPORT &= ~(1<<LCD_PIN_DB7);
	
	//send lower half-byte to IO pins
	if(ucByte & (1<<7))	(DATAPORT |= (1<<LCD_PIN_DB7));
	if(ucByte & (1<<6))	(DATAPORT |= (1<<LCD_PIN_DB6));
	if(ucByte & (1<<5))	(DATAPORT |= (1<<LCD_PIN_DB5));
	if(ucByte & (1<<4))	(DATAPORT |= (1<<LCD_PIN_DB4));

	_delay_ms(1);
	LCD_E(0);
	
	_delay_us(2);
	
	LCD_E(1);
	//clear data IO pins
	DATAPORT &= ~(1<<LCD_PIN_DB4);
	DATAPORT &= ~(1<<LCD_PIN_DB5);
	DATAPORT &= ~(1<<LCD_PIN_DB6);
	DATAPORT &= ~(1<<LCD_PIN_DB7);
	
	//send oreder half-byte to IO pins
	if(ucByte & (1<<3))	(DATAPORT |= (1<<LCD_PIN_DB7));
	if(ucByte & (1<<2))	(DATAPORT |= (1<<LCD_PIN_DB6));
	if(ucByte & (1<<1))	(DATAPORT |= (1<<LCD_PIN_DB5));
	if(ucByte & (1<<0))	(DATAPORT |= (1<<LCD_PIN_DB4));
	_delay_us(1);
	LCD_E(0);
	_delay_ms(50);
}

//function sends command to lcd
void LCD_SendCommand(unsigned char ucCommand)
{
	LCD_RS(0); //RS = 0 to send command
	LCD_SendByte(ucCommand); //send byte
}

//function sends chars to lcd
void LCD_SendChar(unsigned char ucChar)
{
	LCD_RS(1); //RS=1 to send data
	LCD_SendByte(ucChar); //send byte
}

void LCD_ClearScreen(void)
{
	LCD_SendCommand(1<<LCD_CLEAR_DISPLAY);
	_delay_us(1800);
	LCD_SendCommand(1<<LCD_RETURN_HOME);
	_delay_us(1800);
}

//function initalize LCD in 4-bit working mode
void LCD_Initialize(void)
{

	unsigned char i;
	//set data/control ports as output
	_SFR_IO8(_SFR_IO_ADDR(DATAPORT)-1) |= ((1<<LCD_PIN_DB4) | (1<<LCD_PIN_DB5) | (1<<LCD_PIN_DB6) | (1<<LCD_PIN_DB7));
	_SFR_IO8(_SFR_IO_ADDR(CONTROLPORT)-1) |= (1<<LCD_PIN_E | 1<<LCD_PIN_RS);
	
	//
	LCD_RS(0);
	LCD_E(0);
	
	_delay_ms(10);
	
	//enter 4-bit mode, 2 line, 11x8 dots chars
	LCD_E(1);
	DATAPORT |= (1<<LCD_PIN_DB4);
	DATAPORT |= (1<<LCD_PIN_DB5);
	DATAPORT &= ~(1<<LCD_PIN_DB6);
	DATAPORT &= ~(1<<LCD_PIN_DB7);
	_delay_us(10);
	LCD_E(0);
	
	_delay_ms(5);
	
	//send this command onca again to enter 4 bit mode
	for(i =0;i<2; ++i)
	{
		LCD_E(1);
		_delay_us(10);
		LCD_E(0);
		_delay_us(200);
	}
	
	LCD_E(1);
	LCD_SendCommand(1<<LCD_FUNCTION_SET | 1<<LCD_4_BIT_MODE | 1<<LCD_2_LINES_MODE | LCD_CHARS_5x8);
	_delay_ms(50);
	LCD_SendCommand(1<<LCD_MODE_SET | 1<<LCD_SHIFT_ON);
	_delay_ms(50);
	LCD_SendCommand(1<<LCD_DIPLAY_CONTROL | 1<<LCD_BLINKING_ON | 1<<LCD_CURSOR_ON | 1<<LCD_DISPLAY_ON);
	LCD_ClearScreen();
		
}

//function locate cursor in XY coordinates
void LCD_LocateXY(unsigned char ucX,unsigned char ucY)
{
	if(ucY < 0x03 && ucX<0x81)
	{
			LCD_SendCommand(1<<LCD_SET_DDRAM_ADR | (ucY*0x040+ucX));
	}
}

//function shift display window right
void LCD_ShiftRight(unsigned char ucShift, unsigned char ucDelay)
{

	unsigned char ucTemp;
	while(ucShift)
	{
		ucTemp = ucDelay;
		LCD_SendCommand(1<<LCD_SHIFT | 1<<LCD_DISPLAY_SHIFT |  1<<LCD_SHIFT_RIGHT);
		while(ucTemp)
		{
			_delay_ms(2);
			ucTemp--;
		}
		ucShift--;
	}
}

//function shift display window left
void LCD_ShiftLeft(unsigned char ucShift, unsigned char ucDelay)
{
	
	unsigned char ucTemp;
	while(ucShift)
	{
		ucTemp = ucDelay;		
		LCD_SendCommand(1<<LCD_SHIFT | 1<<LCD_DISPLAY_SHIFT |  1<<LCD_SHIFT_LEFT);
		
		while(ucTemp)
		{
			_delay_ms(2);
			ucTemp--;
		}
		ucShift--;
	}
}

//function disable cursor blink
void LCD_CursorBlinkOff(void)
{
	LCD_SendCommand(1<<LCD_DIPLAY_CONTROL | 1<<LCD_DISPLAY_ON | 1<<LCD_CURSOR_ON);
}

//function enables cursor blink
void LCD_CursorBlinkOn(void)
{
	LCD_SendCommand(1<<LCD_DIPLAY_CONTROL | 1<<LCD_DISPLAY_ON | 1<<LCD_CURSOR_ON |1<<LCD_BLINKING_ON);
}

//function turn off cursor
void LCD_CursorOff(void)
{
	LCD_SendCommand(1<<LCD_DIPLAY_CONTROL | 1<<LCD_DISPLAY_ON);
}

//function turn on cursor
void LCD_CursorOn(void)
{
	LCD_SendCommand(1<<LCD_DIPLAY_CONTROL | 1<<LCD_DISPLAY_ON | 1<<LCD_CURSOR_ON);
}

//function dispaly flash string on LCD
void LCD_DisplayString(const char *ccFlashString)
{
	unsigned char Temp = 0;
	while(pgm_read_byte(&ccFlashString[Temp]))
	{
		LCD_SendChar(pgm_read_byte(&ccFlashString[Temp]));
		Temp++;
	}
}

void LCD_DisplayRamString(unsigned char *ucRamString)
{
	unsigned char i=0;
	while(ucRamString[i])
	{
		LCD_SendChar(ucRamString[i]);
		i++;
	}

}

void LCD_DisplayUByte(unsigned char ucByte)
{
	
	unsigned char Temp[3];
	unsigned char i = 2;
	unsigned char j;
	for(j=0;j<3;j++)
		Temp[j]=0;
	j=0;	
	while(ucByte/10)
	{
		Temp[i] = ucByte%10;
		i--; 
		ucByte = ucByte/10;
	}

	Temp[i] = ucByte;
	while(j<3)
	{
		LCD_SendChar(Temp[j] | 0x30);
		j++;
			//do adc specjalnie ;)
	//	if(j==1)
	//	LCD_DisplayString(PSTR("."));
	}

}


void LCD_DisplayUInt(unsigned int uiInt)
{
	
	unsigned char Temp[5];
	unsigned char i = 4;
	unsigned char j;
	for(j=0;j<5;j++)
		Temp[j]=0;
	j=0;	
	while(uiInt/10)
	{
		Temp[i] = uiInt%10;
		i--; 
		uiInt = uiInt/10;
	}

	Temp[i] = uiInt;
	while(j<5)
	{
		LCD_SendChar(Temp[j] | 0x30);
		j++;

	}

}

void LCD_SendText(unsigned char ucUpper[16], unsigned char ucLower[16])
{
	unsigned char i;
	for(i=0;i<16;i++)
	{
		LCD_SendChar(ucUpper[i]);
	}
	
	LCD_SendCommand((1<<LCD_SET_DDRAM_ADR )| 0x040);
	for(i=0;i<16;i++)
	{
		LCD_SendChar(ucLower[i]);
	}
}

void LCD_SendUpper(unsigned char ucUpper[16])
{
	unsigned char i;
	LCD_SendCommand(0x080);
	for(i=0;i<16;i++)
	{
		LCD_SendChar(ucUpper[i]);
	}
}

void LCD_SendLower(unsigned char ucLower[16])
{
	unsigned char i;
	LCD_SendCommand(1<<LCD_SET_DDRAM_ADR | 0x040);
	for(i=0;i<16;i++)
	{
		LCD_SendChar(ucLower[i]);
	}
}
