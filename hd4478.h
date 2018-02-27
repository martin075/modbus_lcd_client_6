<<<<<<< HEAD
/*
************************************************************************  
  Filename	 	-  hd4478.h
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


#ifndef _HD4478_H_
#define _HD4478_H_


//included files
#include <avr/io.h>
#include <util/delay.h>

//data port upravit podla aktulane pouziteho
#define DATAPORT		PORTB
//control port
#define CONTROLPORT		PORTD
#define CONTROLPORT_RS		PORTB
//lcd pins
#define LCD_PIN_RS			4
#define LCD_PIN_E 			7

#define LCD_PIN_DB4 		0
#define LCD_PIN_DB5 		1
#define LCD_PIN_DB6 		2
#define LCD_PIN_DB7 		3

//lcd commands
#define LCD_CLEAR_DISPLAY	0x00
#define LCD_RETURN_HOME		0x01

#define LCD_MODE_SET		0x02
//------------------------------
#define LCD_SHIFT_ON		0x01

//display control
#define LCD_DIPLAY_CONTROL	0x03
//------------------------------
#define LCD_DISPLAY_ON		0x02
#define LCD_CURSOR_ON		0x01
#define LCD_BLINKING_ON		0x00

//shift options
#define LCD_SHIFT			0x04
//------------------------------
#define LCD_CURSOR_SHIFT	0x04
#define LCD_DISPLAY_SHIFT	0x03
#define LCD_SHIFT_LEFT		0x02
#define LCD_SHIFT_RIGHT		0x04

#define LCD_FUNCTION_SET	0x05
//------------------------------
#define LCD_4_BIT_MODE		0x05
#define LCD_2_LINES_MODE	0x03
#define LCD_1_LINE_MODE		0x05
#define LCD_CHARS_5x11		0x05
#define LCD_CHARS_5x8		0x02

#define LCD_SET_CGRAM_ADR	0x06

#define LCD_SET_DDRAM_ADR	0x07




//function controlling pin E
void LCD_E(unsigned char ucE);

//function controlling pin RS
void LCD_RS(unsigned char ucRS);

//function initializing display
void LCD_Initialize(void);

//function clear screen
void LCD_ClearScreen(void);

//functon divide byte to two 4 bit parts
void LCD_SendByte(unsigned char ucByte);

//function send command to lcd
void LCD_SendCommand(unsigned char ucCommand);

//function send char to lcd
void LCD_SendChar(unsigned char ucChar);



//function send text on visable
void LCD_SendText(unsigned char ucUpper[16], unsigned char ucLower[16]);

void LCD_SendUpper(unsigned char ucUpper[16]);
void LCD_SendLower(unsigned char ucLower[16]);

//function locate the place where text is apper
void LCD_LocateXY(unsigned char ucX,unsigned char ucY);

void LCD_ShiftRight(unsigned char Shift, unsigned char ucDelay);

void LCD_ShiftLeft(unsigned char Shift, unsigned char ucDelay);

//cursor eable
void LCD_CursorOn(void);

//curasor disable
void LCD_CursorOff(void);

//function enable cursor blinking
void LCD_CursorBlinkOn(void);

//function disable cursor blinking
void LCD_CursorBlinkOff(void);

//function sends string from flash to lcd
void LCD_DisplayString(const char *ccFlashString);

void LCD_DisplayRamString(unsigned char *ucRamString);

void LCD_DisplayUByte(unsigned char ucByte);
//function
void LCD_DisplayUInt(unsigned int uiInt);

#endif
=======
/*
************************************************************************  
  Filename	 	-  hd4478.h
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


#ifndef _HD4478_H_
#define _HD4478_H_


//included files
#include <avr/io.h>
#include <util/delay.h>

//data port upravit podla aktulane pouziteho
#define DATAPORT		PORTB
//control port
#define CONTROLPORT		PORTD
#define CONTROLPORT_RS		PORTB
//lcd pins
#define LCD_PIN_RS			4
#define LCD_PIN_E 			7

#define LCD_PIN_DB4 		0
#define LCD_PIN_DB5 		1
#define LCD_PIN_DB6 		2
#define LCD_PIN_DB7 		3

//lcd commands
#define LCD_CLEAR_DISPLAY	0x00
#define LCD_RETURN_HOME		0x01

#define LCD_MODE_SET		0x02
//------------------------------
#define LCD_SHIFT_ON		0x01

//display control
#define LCD_DIPLAY_CONTROL	0x03
//------------------------------
#define LCD_DISPLAY_ON		0x02
#define LCD_CURSOR_ON		0x01
#define LCD_BLINKING_ON		0x00

//shift options
#define LCD_SHIFT			0x04
//------------------------------
#define LCD_CURSOR_SHIFT	0x04
#define LCD_DISPLAY_SHIFT	0x03
#define LCD_SHIFT_LEFT		0x02
#define LCD_SHIFT_RIGHT		0x04

#define LCD_FUNCTION_SET	0x05
//------------------------------
#define LCD_4_BIT_MODE		0x05
#define LCD_2_LINES_MODE	0x03
#define LCD_1_LINE_MODE		0x05
#define LCD_CHARS_5x11		0x05
#define LCD_CHARS_5x8		0x02

#define LCD_SET_CGRAM_ADR	0x06

#define LCD_SET_DDRAM_ADR	0x07




//function controlling pin E
void LCD_E(unsigned char ucE);

//function controlling pin RS
void LCD_RS(unsigned char ucRS);

//function initializing display
void LCD_Initialize(void);

//function clear screen
void LCD_ClearScreen(void);

//functon divide byte to two 4 bit parts
void LCD_SendByte(unsigned char ucByte);

//function send command to lcd
void LCD_SendCommand(unsigned char ucCommand);

//function send char to lcd
void LCD_SendChar(unsigned char ucChar);



//function send text on visable
void LCD_SendText(unsigned char ucUpper[16], unsigned char ucLower[16]);

void LCD_SendUpper(unsigned char ucUpper[16]);
void LCD_SendLower(unsigned char ucLower[16]);

//function locate the place where text is apper
void LCD_LocateXY(unsigned char ucX,unsigned char ucY);

void LCD_ShiftRight(unsigned char Shift, unsigned char ucDelay);

void LCD_ShiftLeft(unsigned char Shift, unsigned char ucDelay);

//cursor eable
void LCD_CursorOn(void);

//curasor disable
void LCD_CursorOff(void);

//function enable cursor blinking
void LCD_CursorBlinkOn(void);

//function disable cursor blinking
void LCD_CursorBlinkOff(void);

//function sends string from flash to lcd
void LCD_DisplayString(const char *ccFlashString);

void LCD_DisplayRamString(unsigned char *ucRamString);

void LCD_DisplayUByte(unsigned char ucByte);
//function
void LCD_DisplayUInt(unsigned int uiInt);

#endif
>>>>>>> origin/master
