// DS18B20 - +-0,5°C
// BMP180 - +-1°C, -4 +2 hPa
// fuses set for Atmega328P L-C6, H-DD
// modbus implemented by using Max B. mbs38 at github code
//--------------------------------------------------------
// missing thermostat function, for range 0-90°C
// write thermostat temperature
// write delay between reading values , for range 0-100 sec
//-----------------------------

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
#include "yaMBSiavr.h"

//#define MODE_altitude 7			// altitude correction for relative barometric pressure
#define clientAddress 0x0A // slave address

//--------------------
#define adr_thermostat1	 	0x02
#define adr_thermostat2	 	0x04		//adr in EEPROM - for MODBUS,word - int- 2Byte
#define adr_delay_read		0x06
//-------------------- 

//modbus 
uint8_t back_len0 = 0;
uint8_t slave_add; 
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
//int32_t gAltitudeCorr=0; // altitude correction for relative barometric pressure
int32_t gPressCorr=0;
long l;
double d;
//float d; // in gcc float and double has the same 4B
char printbuff[10];

//------modbus
// ----------premenne ------------------
volatile uint8_t instate = 0;
volatile uint8_t outstate = 0;
volatile uint16_t inputRegisters[4];
volatile uint16_t holdingRegisters[12]= {40,41,42,43,44,45,47,48,24,28,15,0}; // values for example

void timer0100us_start(void) {
	TCCR0B|=(1<<CS01); //prescaler 8
	TIMSK0|=(1<<TOIE0);
}

/*
*   Modify the following 3 functions to implement your own pin configurations...
*/
// output bits
void SetOuts(volatile uint8_t in) {
	//PORTD|= (((in & (1<<3))<<4) | ((in & (1<<4))<<1) | ((in & (1<<5))<<1));
	//PORTB|= (((in & (1<<0))<<2) | ((in & (1<<1))) | ((in & (1<<2))>>2));
	in=~in;
	//PORTB&= ~(((in & (1<<0))<<2) | ((in & (1<<1))) | ((in & (1<<2))>>2));
	//PORTD&= ~(((in & (1<<3))<<4) | ((in & (1<<4))<<1) | ((in & (1<<5))<<1));
}

// input bits
uint8_t ReadIns(void) {
	uint8_t ins=0x00;
	//ins|=(PINC&((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)));
	//ins|=(((PIND&(1<<4))<<2)|((PIND&(1<<3))<<4));
	return ins;
}

void io_conf(void) { 
	/*
	 Outputs: PB2,PB1,PB0,PD5-rele,PD6-rele,PD7
	 Inputs: PC0, PC1, PC2, PC3, PC4, PC6, PD4, PD3
	*/
	DDRD=0x00;
	
	PORTD=0x00;
	PORTD|=(1<<0);
	//DDRD |= (1<<2)|(1<<5)|(1<<6)|(1<<7);
	DDRD |= (1<<2);

	DDRD = (1<<PD5) | (1<<PD6);	// output for rele
	//PORTD |= (1<<PD5) | (1<<PD6); //set log.1
	PORTD &=~(1<<PD5);		// set log. 0
	PORTD &=~(1<<PD6);		// set log. 0
}




void modbusGet(void) {
	if (modbusGetBusState() & (1<<ReceiveCompleted))
	{
		switch(rxbuffer[1]) {
			case fcReadCoilStatus: {
				modbusExchangeBits(&outstate,0,8);
			}
			break;
			
			case fcReadInputStatus: {
				volatile uint8_t inps = ReadIns();
				modbusExchangeBits(&inps,0,8);
			}
			break;
			
			case fcReadHoldingRegisters: {
				modbusExchangeRegisters(holdingRegisters,0,12);
			}
			break;
			
			case fcReadInputRegisters: {
				modbusExchangeRegisters(inputRegisters,0,4);
			}
			break;
			
			case fcForceSingleCoil: {
				modbusExchangeBits(&outstate,0,8);
				SetOuts(outstate);
			}
			break;
			
			case fcPresetSingleRegister: {
				modbusExchangeRegisters(holdingRegisters,0,12);
			}
			break;
			
			case fcForceMultipleCoils: {
				modbusExchangeBits(&outstate,0,8);
				SetOuts(outstate);
			}
			break;
			
			case fcPresetMultipleRegisters: {
				modbusExchangeRegisters(holdingRegisters,0,12);
			}
			break;
			
			default: {
				modbusSendException(ecIllegalFunction);
			}
			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////

int main(void)
{
	int desatiny,cele,j,press=20;
	unsigned char i,chyba1=0,chyba2=0,chyba3=0,chyba4=0,chyba5=0,chyba6=0;
    int thermostat1,thermostat2,delay_read,relative_corr;
	int thermostat1_eeprom,thermostat2_eeprom,delay_read_eeprom; //24dec18hex,28dec1C,6dec6hex
	int interval;	// interval*10ms,for example 1000*10ms = 10sec	   

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
	//modbus------------------------------------------------------
	io_conf();	
	modbusSetAddress(clientAddress); // setting client address
	modbusInit();
	//wdt_enable(7);
	timer0100us_start();
	//---------------------------------------------------------
	//deny interrupt
	cli(); 
	//Watchdog initialization.
	//wdt_reset();
	//wdt_enable(WDTO_8S); // for 5V supply,  At lower supply voltages, the times will increase 
	

	thermostat1_eeprom = eeprom_read_word((uint16_t*)adr_thermostat1);   

	thermostat2_eeprom = eeprom_read_word((uint16_t*)adr_thermostat2);   

	delay_read_eeprom = eeprom_read_word((uint16_t*)adr_delay_read);
	

	if((thermostat1_eeprom>0)&&(thermostat1_eeprom<90))
		{
		holdingRegisters[8] = thermostat1 = thermostat1_eeprom;
		}
		else 
		{ 	thermostat1_eeprom=24;
			eeprom_write_word((uint16_t*)adr_thermostat1,thermostat1_eeprom); // works
		}

	if((thermostat2_eeprom>0)&&(thermostat2_eeprom<90))
		{
		holdingRegisters[9] = thermostat2 = thermostat2_eeprom;
		}
		else 
		{thermostat2_eeprom=28;
		eeprom_write_word((uint16_t*)adr_thermostat2,thermostat2_eeprom); // works
		}

	if((delay_read_eeprom>0)&&(delay_read_eeprom<100))
		{
		holdingRegisters[10] = delay_read = delay_read_eeprom;
		}
		else 
		{delay_read_eeprom=10;
		eeprom_write_word((uint16_t*)adr_delay_read,delay_read_eeprom);
		}

	 lcd_init( LCD_DISP_ON);
	 lcd_clrscr();
	 //_delay_ms(80);
	
	 lcd_gotoxy( 0, 0);
	 lcd_puts_P( " modbus temp 0.2\n");
	 //lcd_gotoxy( 1, 1);
	sprintf( CharBuffer, "%i,8N1\n",BAUD);
	lcd_puts(CharBuffer);
	sprintf( CharBuffer, "modbus adr:%X\n",clientAddress);
	lcd_puts(CharBuffer);
	sprintf( CharBuffer, "t1:%+i;t2:%+i",thermostat1,thermostat2);
	lcd_puts(CharBuffer);
	 _delay_ms(2000);
	 //-------------------------------------
	 lcd_clrscr();
	 lcd_gotoxy( 2, 1);		//column , row
	 lcd_puts_P( "kontrola snimacov");
	 lcd_gotoxy( 3, 2);		//column , row
	 lcd_puts_P( "DS18b20"); // msg0
	 _delay_ms(1000);
	 lcd_clrscr();
	//---------------------------------
	lcd_gotoxy( 0, 0); // stlpec-riadok
	lcd_puts_P( "S1:");
	Device1Presence = ds18b20_reset(&PORTC,PC0);
	lcd_gotoxy( 4, 0);
	if(Device1Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 4, 0);lcd_puts_P( "----");chyba1=1;}
	//_delay_ms(100);
	//---------------------------------
	Device2Presence = ds18b20_reset(&PORTC,PC1);
	lcd_gotoxy( 0, 1);
	lcd_puts_P( "S2:");
	lcd_gotoxy( 4, 1);
	if(Device2Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 4, 1);lcd_puts_P( "----");chyba2=1;}
	//_delay_ms(100);
	//---------------------------------
	Device3Presence = ds18b20_reset(&PORTC,PC2);
	lcd_gotoxy( 0, 2);
	lcd_puts_P( "S3:");
	lcd_gotoxy( 4, 2);
	if(Device3Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 4, 1);lcd_puts_P( "----");chyba3=1;}
	//_delay_ms(100);
	//---------------------------------
	Device4Presence = ds18b20_reset(&PORTC,PC3);
	lcd_gotoxy( 0, 3);
	lcd_puts_P( "S4:");
	lcd_gotoxy( 4, 3);

	if(Device4Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 4, 3);lcd_puts_P( "----");chyba4=1;}
	//---------------------------------
	Device5Presence = ds18b20_reset(&PORTD,PD3);
	lcd_gotoxy( 9, 2);
	lcd_puts_P( "S5:");
	lcd_gotoxy( 11, 2);

	if(Device5Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 9, 2);lcd_puts_P( "----");chyba5=1;}
	//---------------------------------
	Device6Presence = ds18b20_reset(&PORTD,PD4);
	lcd_gotoxy( 9, 3);
	lcd_puts_P( "S6:");
	lcd_gotoxy( 11, 3);

	if(Device6Presence)
			lcd_puts_P( "OK");
		else {  lcd_gotoxy( 9, 3);lcd_puts_P( "----");chyba6=1;}

	_delay_ms(1000);

// ----------print ROM code----------------

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

		wdt_reset(); 
		sei();
	//----------------------------------------------------	
		if(chyba1==0)
		{
		CurrentTemp1 = ds18b20_gettemp(&PORTC,PC0); // decicelsius
		cele = CurrentTemp1/10;
		desatiny = ( abs(CurrentTemp1) - abs((cele*10)) );
		lcd_gotoxy( 3, 0);
		sprintf( CharBuffer, "%+i.%i\n",cele,desatiny);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 9, 0);
		lcd_putc(0); // print user character on LCD
		//lcd_putc(1);
		//lcd_putc(2);
	//----------------------------------------------------	
			
		if(chyba2==0)
		{
		CurrentTemp2 = ds18b20_gettemp(&PORTC,PC1);
		cele = CurrentTemp2/10;
		desatiny = (abs(CurrentTemp2) - abs((cele*10)) );
		sprintf( CharBuffer, "%+i.%i\n",cele,desatiny);
		//sprintf( CharBuffer, "%i \xC6\n",CurrentTemp2); // xC6, xC5 arrows
		lcd_gotoxy( 3, 1);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 9, 1);
		lcd_putc(0); // print user character on LCD
			
		//_delay_ms(100);
	//----------------------------------------------------	
		if(chyba3==0)
		{
		CurrentTemp3 = ds18b20_gettemp(&PORTC,PC2);
		cele = CurrentTemp3/10;
		desatiny = (abs(CurrentTemp3) - abs((cele*10)) );
		
		sprintf( CharBuffer, "%+i.%i\n",cele,desatiny);
		lcd_gotoxy( 3, 2);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 9, 2);
		lcd_putc(0); // print user character on LCD
			
		//_delay_ms(100);
	//----------------------------------------------------	
		if(chyba4==0)
		{
		CurrentTemp4 = ds18b20_gettemp(&PORTC,PC3);
		cele = CurrentTemp4/10;
		desatiny = (abs(CurrentTemp4) - abs((cele*10)) );
		sprintf( CharBuffer, "%+i.%i\n",cele,desatiny);
		lcd_gotoxy( 3, 3);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 9, 3);
		lcd_putc(0); // print user character on LCD
			
		//_delay_ms(100);
	//----------------------------------------------------			
		if(chyba5==0)
		{
		CurrentTemp5 = ds18b20_gettemp(&PORTD,PD3);
		cele = CurrentTemp5/10;
		desatiny = (abs(CurrentTemp5) - abs((cele*10)) );
		sprintf( CharBuffer, "%+i.%i",cele,desatiny);
		//sprintf( CharBuffer, "%i\xC6\n",CurrentTemp4);
		lcd_gotoxy( 14, 2);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 19, 2);
		lcd_putc(0); // print user character on LCD
	//----------------------------------------------------			
		if(chyba6==0)
		{
		CurrentTemp6 = ds18b20_gettemp(&PORTD,PD4);
		cele = CurrentTemp6/10;
		desatiny = (abs(CurrentTemp6) - abs((cele*10)) );
		sprintf( CharBuffer, "%+i.%i",cele,desatiny);
		//sprintf( CharBuffer, "%i\xC6\n",CurrentTemp4);
		lcd_gotoxy( 14, 3);
		lcd_puts(CharBuffer);
		}
		lcd_gotoxy( 19, 3);
		lcd_putc(0); // print user character on LCD	
		//_delay_ms(100);
	//----------------------------------------------------			
		
	//get temperature BMP085
		d = bmp085_gettemperature();
		cele = d/10;
		desatiny = abs(d) - abs(cele*10);
		sprintf( CharBuffer, "%+i.%i",cele,desatiny);
		//ltoa((d*10), printbuff, 10); // for long conversion function to string
		lcd_gotoxy( 14, 1);
		lcd_puts(CharBuffer);
		//lcd_puts( printbuff);
		lcd_putc(0); // print user character on LCD
		//_delay_ms(100);
		
		if(press==20)
		{
		//get pressure BMP085
		l = bmp085_getpressure(gPressCorr*100);			// in Pa. correction in hPa, 32hPa for Kosice
		//l = bmp085_getpressure(gAltitudeCorr*100); // in hPa 
		//ltoa(l, printbuff, 10);  				// convert long to string , for UART
		lcd_gotoxy( 17, 0);
		lcd_puts_P( "hPa");
		lcd_gotoxy( 13, 0);
		ltoa((l) , printbuff, 10); // in hPa (/100) in relative pressure to sea level, bmp085.h , for LCD
		lcd_puts( printbuff);
		press=0;
		}	
		//wdt_reset();
		//modbus-------------------------
		holdingRegisters[0]=CurrentTemp1;
		holdingRegisters[1]=CurrentTemp2;
		holdingRegisters[2]=CurrentTemp3;
		holdingRegisters[3]=CurrentTemp4;
		holdingRegisters[4]=CurrentTemp5;
		holdingRegisters[5]=CurrentTemp6;
		holdingRegisters[6]= l/10; //10*Pa
		holdingRegisters[7]= d;

		thermostat1 = holdingRegisters[8];	// from master 
		thermostat2 = holdingRegisters[9];
		delay_read = holdingRegisters[10];	// from master in seconds
		relative_corr = holdingRegisters[11];

	if((delay_read > 1) && (delay_read <200))
		{ interval = delay_read*100;
		//
		if(delay_read_eeprom != delay_read)
			{
			cli();
			eeprom_write_word((uint16_t*)adr_delay_read,delay_read);
			sei();
			delay_read_eeprom = delay_read;
			}
			else delay_read_eeprom = delay_read;
		}
		else interval = 15;

	if((thermostat1>0)&&(thermostat1<90))
		{
		if((thermostat1*10)> (CurrentTemp2 + 50))
			{ PORTD |= (1<<PD5);//set PD5 to 1
			}
		if(thermostat1 != thermostat1_eeprom)
			{cli();	
			eeprom_write_word((uint16_t*)adr_thermostat1,thermostat1); // works
			sei();
			thermostat1_eeprom = thermostat1;
			}
		}
		else thermostat1 = thermostat1_eeprom;

	if((relative_corr>0) && (relative_corr<100))
		{gPressCorr = relative_corr;
		}
		else gPressCorr = 0;

	if((thermostat2*10)> (CurrentTemp4 + 50))
		{ PORTD |= (1<<PD6);//set PD6 to 1
		}
	lcd_gotoxy( 11, 3);
	sprintf( CharBuffer, "%i.%i",thermostat1,delay_read);
	lcd_puts(CharBuffer);
		// end of loop--------------------
		// enable interrupt
		sei();
			// loop for communication, and delay between reading temperatures
		for(j=0;j<interval;j++)
			{
			modbusGet();
			_delay_ms(10);
			}//for(j
		press++; // increment press - more delay for measurment of atmospheric pressure

	}	// while
		//main
}


/// INTERRUPT ///

ISR(TIMER0_OVF_vect) { //this ISR is called 9765.625 times per second, CPU-20MHz
	modbusTickTimer();
}
 
