/*
************************************************************************  
  Filename	 	-  onewire.h
  Author 		-  BESEA Robotics
  Date 			-  2017-03-2011
  Processor 	-  Atmel ATmega32/16/8 and similar
  Description	: 
  Dallas-Maxim one wire devices.
************************************************************************ 
*/
#ifndef _ONE_WIRE_H_
#define _ONE_WIRE_H_

//#define F_CPU 8000000UL //defined in AS
//included files
#include <avr/io.h>
#include <util/delay.h>

unsigned char OW_Reset(volatile unsigned char *Port, unsigned char Pin); //reset one wire bus, if no device on bus return 0
void OW_WriteByte(unsigned char Byte, volatile unsigned char *Port, unsigned char Pin); //write one byte to one wire bus
unsigned char OW_ReadByte(volatile unsigned char *Port, unsigned char Pin); //read one byte from device
void OW_ReadScratchpad(unsigned char *Buffer,volatile unsigned char *Port,unsigned char Pin); //read scratchpad
int OW_GetRawTemperature(unsigned char CRCStatus,volatile unsigned char *Port,unsigned char Pin); //get 2 bytes temp
void OW_Initialization(volatile unsigned char *Port, unsigned char Pin);
void OW_FormatRawTemperature(unsigned char *CharBuffer,int RawTemperature,unsigned char Accuracy);
char OW_CompareTemperature(int RawTemperature,char MyTemperature, char MyTemperatureFrac);
#endif
