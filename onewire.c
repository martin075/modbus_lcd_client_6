/*
************************************************************************  
  Filename	 	-  onewire.C
  Author 		-  BESEA Robotics
  Date 			-  21-02-2012
  Processor 	-  Atmel ATmega32/16/8 and similar
  Description	: 
  Dallas-Maxim DS18x20 one wire devices.
  
  modified 11/2017 - martin
************************************************************************ 
*/

#include "onewire.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>


//reset one wire bus and check device presence
unsigned char OW_Reset(volatile unsigned char *Port, unsigned char Pin)
{
	unsigned char PresencePulse=0;
	unsigned char BusRealese=0;
	*Port &=~(1<<Pin); //1W pin low
	*(Port-1)|=(1<<Pin); //pin as output
	
	_delay_us(500); //delay min 480 us
	*(Port-1)&=~(1<<Pin); //pin as input without pullup
	
	_delay_us(60); // wait for device response
	if((*(Port-2))&(1<<Pin)) {PresencePulse = 0;} else {PresencePulse = 1;}
	_delay_us(250); //device after 15-60us pull down line for 60-240us
	if((*(Port-2))&(1<<Pin)) {BusRealese = 1;} else {BusRealese = 0;}
	return(PresencePulse&BusRealese); //return presence bit(0-no device,1-device OK)
}

//write one byte on one wire bus
void OW_WriteByte(unsigned char Byte, volatile unsigned char *Port, unsigned char Pin)
{
	unsigned char Mask =0x01;
	unsigned char i;

	*(Port-1)|=(1<<Pin); // DQ pin output

	for(i=0;i<8;i++) //by all 8 bits
	{
		if(Byte&Mask) //if bit=1
		{
			*Port &=~(1<<Pin); //DQ low
			_delay_us(4);
			*Port |=(1<<Pin); //DQ high
			_delay_us(76);
		}

		else //if bit 0
		{
			*Port &=~(1<<Pin); //DQ low
			_delay_us(80);
			*Port |=(1<<Pin); //DQ high
			_delay_us(5);
		}
		Mask<<=1; //shift mask to next bit
	}
}

//read one byte from one wire bus
unsigned char OW_ReadByte(volatile unsigned char *Port, unsigned char Pin)
{
	unsigned char Byte=0;
	unsigned char i;
	for(i=0;i<8;i++)
	{
		*(Port-1)|=(1<<Pin); //pin as output
		*Port&=~(1<<Pin); //DQ low
		_delay_us(2);
		*(Port-1)&=~(1<<Pin); //pin as in
		_delay_us(10);
		Byte |=(((*(Port-2))&(1<<Pin))<<i);	//collect data
		_delay_us(60);
	}
	return(Byte);
}

//read 8 bytes scratchpad from DS18x20
void OW_ReadScratchpad(unsigned char *Buffer, volatile unsigned char *Port, unsigned char Pin)
//void OW_ReadScratchpad(char *Buffer, volatile unsigned char *Port, unsigned char Pin)
{
	unsigned char i;
	for(i=0;i<9;i++)
	{
		Buffer[i]= OW_ReadByte(Port,Pin);
	}
}

//get unformated temperature and check CRC
int OW_GetRawTemperature(unsigned char CRCStatus,volatile unsigned char *Port,unsigned char Pin)
//int16_t OW_GetRawTemperature(unsigned char CRCStatus,volatile unsigned char *Port,unsigned char Pin)
{
	//crc table coeffs
	const static unsigned char CRCTable8[] PROGMEM={
	0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
	157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
	35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
	190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
	70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
	219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
	101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
	248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
	140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
	17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
	175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
	50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
	202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
	87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
	233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
	116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53};

	unsigned char ScratchapadBuffer[9]; //read scratchpad
	unsigned char CRC8Temp;
	unsigned char iCRC;	//loop iteration
	unsigned char *CRCStatusPtr; //error flag pointer
	CRCStatusPtr=&CRCStatus; //set pointer on flag 
	OW_Reset(Port,Pin);	//OW reset
	OW_WriteByte(0xCC,Port,Pin); //skip ROM (no adress sending)
	OW_WriteByte(0xBE,Port,Pin); //read scratchpad cmd
	OW_ReadScratchpad(ScratchapadBuffer,Port,Pin); //reading scratchpad
	//check CRC
	for(iCRC=0;iCRC<8;iCRC++)	//calculate crc
	{
		CRC8Temp=pgm_read_byte(&CRCTable8[iCRC])^ScratchapadBuffer[iCRC];
		
	}
	if(CRC8Temp != ScratchapadBuffer[8]) //check result
		*CRCStatusPtr=1;
	else
		*CRCStatusPtr=0;
	//prepare next temperature read..... 
	OW_Reset(Port,Pin); //reset again
	OW_WriteByte(0xCC,Port,Pin); //skip ROM
	OW_WriteByte(0x44,Port,Pin); //convert temperature
	return(ScratchapadBuffer[0]|(ScratchapadBuffer[1]<<8)); //return 2 temperature bytes
}

//convert RAW to ASCII format
//sprintf format, not ASCII - modified 11/2017
//void OW_FormatRawTemperature(unsigned char *CharBuffer,int RawTemperature, unsigned char Accuracy) // origin

void OW_FormatRawTemperature(unsigned char *CharBuffer,int RawTemperature)
{
		int temperature, decimal;
		int RawTemperatureMSB,RawTemperatureLSB;
		//unsigned char RawTemperatureMSB,RawTemperatureLSB;	
		//unsigned char Temp[3];
		//unsigned char i = 2;
		//unsigned char j;
		unsigned char Sign=0;  //default is positive number

		//format ASCII string from DS data
		if(RawTemperature&0x0800)//if negative number
		{
			//RawTemperature =0xFFFF-RawTemperature+1;
			Sign=1;
		}

		RawTemperatureLSB =RawTemperature&0x000F;
		RawTemperatureMSB=(RawTemperature>>4);
		//*****************************************start of new added
		//RawTemperature = RawTemperatureLSB*625;
		
		if(Sign == 0)
		{
		temperature = (RawTemperatureLSB & 0xF0) >> 4 | (RawTemperatureMSB & 0x0F) << 4 ;   // signed teplota
		decimal = (RawTemperatureLSB & 0x0F) * 0.625;
		decimal = decimal;
		//retd = 10 * temperature;  // decicelsius
		//retd = retd + decimal;
		}
		else
			{
			RawTemperatureLSB =~ RawTemperatureLSB;
			RawTemperatureMSB =~ RawTemperatureMSB;
			temperature = (RawTemperatureLSB & 0xF0) >> 4 | (RawTemperatureMSB & 0x0F) << 4 ;   // signed teplota
			decimal = ((RawTemperatureLSB + 1) & 0x0F) * 0.625;
			decimal = decimal;
			//retd = (temperature*10 + decimal)*(-1);
			}
		//sprintf( CharBuffer, "%d \xC6\n",32);
		//itoa(temperature,CharBuffer,10);
		sprintf( CharBuffer, "%d \xC6\n",temperature); //temperature with arrow
		//*****************************************end of new added
		/*
		for(j=0;j<3;j++)
			Temp[j]=0; //clear temp

		j=0;	
		while(RawTemperatureMSB/10)
		{
			Temp[i] = RawTemperatureMSB%10;
			i--; 
			RawTemperatureMSB = RawTemperatureMSB/10;
		}
		Temp[i] = RawTemperatureMSB;

		while(j<3)
		{
			CharBuffer[j] = Temp[j] | 0x30;
			j++;
		}

		if(CharBuffer[0]=='0' && CharBuffer[1]=='0')
		{
			CharBuffer[0]=' ';
			CharBuffer[1]=' ';
		}

		
		if(CharBuffer[0]=='0' && CharBuffer[1]!='0')
		{
			CharBuffer[0]=' ';
		}

		if(Sign)
		{
			CharBuffer[0]='-';
		}

		CharBuffer[3] ='.';
		
		RawTemperature = RawTemperatureLSB*625;

		i=2;
		j=0;

		while(i)
		{
			Temp[i] = RawTemperature%10;
			i--; 
			RawTemperature = RawTemperature/10;
		}

		while(j<3)
		{
			CharBuffer[j+4] = Temp[j] | 0x30;
			j++;
		}
*/		
		/*	
		switch(Accuracy)
		{
		
			case 0:
			CharBuffer[3]=0;
			break;
	
			case 1:
			CharBuffer[5]=0;
			break;

			default:
			CharBuffer[7]=0;
			break;
		}
		*/
}

//send DS 2x conversion command for proper runup
void OW_Initialization(volatile unsigned char *Port, unsigned char Pin)
{
	int Temp0;
	unsigned char Temp1=1;
	_delay_ms(200); //small delay
	Temp0 = OW_GetRawTemperature(Temp1,Port,Pin);
	_delay_ms(500);
	_delay_ms(500); //wait for conversion end
	Temp0 = OW_GetRawTemperature(Temp1,Port,Pin);
	Temp0 = Temp0; // for warning
	_delay_ms(500);
	_delay_ms(500); //wait for conversion end
}

char OW_CompareTemperature(int RawTemperature,char MyTemperature, char MyTemperatureFrac)
{
	unsigned char ComparedTemperature = (MyTemperature<<4)|(((MyTemperatureFrac*1000)/625)&0x000F);
	if(RawTemperature<ComparedTemperature)
		return -1;
	if(RawTemperature>ComparedTemperature)
		return 1;
	else
		return 0;
}

