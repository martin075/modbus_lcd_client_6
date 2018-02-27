<<<<<<< HEAD
void read_rom()
{
	volatile unsigned char info[8];
		int i;
		int j;
		disableInterrupts();
		therm_reset(); 
		therm_write_byte(THERM_CMD_READROM);
	for(i=0;i<8;i++)
	{
		info[i]=therm_read_byte();
	}
	enableInterrupts(); 

	//i=0;
	LCD_CLEAR_DISPLAY();

	for(j=0;j<8;j++)
	{
	for(i=0;i<8;i++)
	 {
		if((info[j])& 1<<(7-i))
			LCD_printchar('1');
		else
			LCD_printchar('0');
	 }
	Delay_ms(3000);
	LCD_CLEAR_DISPLAY();
	//i=0;
	}
}


//---------------------
unsigned temp;
char sernum;
int i;
int colona;
char *sernum_hex[8];

/ Format and display result on Lcd
    Display_Temperature(temp);


    Ow_Reset(&PORTE, 2);                         // Onewire reset signal
    Ow_Write(&PORTE, 2, 0x33);                   // Read ROM
    Delay_us(120);

       colona = 17;
       for(i = 0; i <= 7; i++)
          {
            colona = colona - 2;
            sernum = Ow_Read(&PORTE, 2);
            bytetohex(sernum, sernum_hex);
            Lcd_Out(1, colona, sernum_hex);
          }
=======
void read_rom()
{
	volatile unsigned char info[8];
		int i;
		int j;
		disableInterrupts();
		therm_reset(); 
		therm_write_byte(THERM_CMD_READROM);
	for(i=0;i<8;i++)
	{
		info[i]=therm_read_byte();
	}
	enableInterrupts(); 

	//i=0;
	LCD_CLEAR_DISPLAY();

	for(j=0;j<8;j++)
	{
	for(i=0;i<8;i++)
	 {
		if((info[j])& 1<<(7-i))
			LCD_printchar('1');
		else
			LCD_printchar('0');
	 }
	Delay_ms(3000);
	LCD_CLEAR_DISPLAY();
	//i=0;
	}
}


//---------------------
unsigned temp;
char sernum;
int i;
int colona;
char *sernum_hex[8];

/ Format and display result on Lcd
    Display_Temperature(temp);


    Ow_Reset(&PORTE, 2);                         // Onewire reset signal
    Ow_Write(&PORTE, 2, 0x33);                   // Read ROM
    Delay_us(120);

       colona = 17;
       for(i = 0; i <= 7; i++)
          {
            colona = colona - 2;
            sernum = Ow_Read(&PORTE, 2);
            bytetohex(sernum, sernum_hex);
            Lcd_Out(1, colona, sernum_hex);
          }
>>>>>>> origin/master
