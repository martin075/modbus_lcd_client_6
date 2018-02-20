static const PROGMEM unsigned char copyRightChar[] =
{
	0x07, 0x08, 0x13, 0x14, 0x14, 0x13, 0x08, 0x07,
	0x00, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x00
};
...
       /*
        * load two userdefined characters from program memory
        * into LCD controller CG RAM location 0 and 1
        */
       lcd_command(_BV(LCD_CGRAM));  /* set CG RAM start address 0 */
       for(i=0; i<16; i++)
       {
           lcd_data(pgm_read_byte_near(&copyRightChar[i]));
       }
       
       /* move cursor to position 0 on line 2 */
       /* Note: this switched back to DD RAM adresses */
       lcd_gotoxy(0,1);
       
       /* display user defined (c), built using two user defined chars */
       lcd_putc(0);
       lcd_putc(1);