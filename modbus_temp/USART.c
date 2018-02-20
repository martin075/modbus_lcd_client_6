// Atmega 8,48,88,168,128,162,328P
// Ivan orfanidi
// 

#include "USART.h"

	uint8_t rx_rd_counter_index0;
	uint8_t rx_counter_index0;
	char rx_buffer0[RX_BUFFER_SIZE0];

	uint8_t tx_wr_counter_index0;
	uint8_t tx_counter_index0;
	char tx_buffer0[TX_BUFFER_SIZE0];

	#if defined (__AVR_ATmega162__) || (__AVR_ATmega128__)

		uint8_t rx_rd_counter_index1;
		uint8_t rx_counter_index1;
		char rx_buffer1[RX_BUFFER_SIZE1];

		uint8_t tx_wr_counter_index1;
		uint8_t tx_counter_index1;
		char tx_buffer1[TX_BUFFER_SIZE1];

	#endif



void usart0_write_str(char *pData_Usart0)
{
	while(usart0_busy_wait());

	uint16_t i=0;

	while(pData_Usart0[i]!=0)
	{
		usart0_write(pData_Usart0[i]);

		if(pData_Usart0[i]=='\n')
		{
			_delay_ms(USART0_DELAY_MS);
			usart0_write('\r');
		}

		i++;

		_delay_ms(USART0_DELAY_MS);
	}
	
}


#if defined (__AVR_ATmega48__) || (__AVR_ATmega48P__) || (__AVR_ATmega88__) || (__AVR_ATmega88P__) || (__AVR_ATmega168__) || (__AVR_ATmega168P__)|| (__AVR_ATmega328P__)	//If ATmega 48/64/168

// USART INITIALIZATION BAUD RATE//
void usart0_init()
{

	if(u2x0)
	{

			UBRR0L = (uint16_t)((F_CPU/BAUD_RATE0/16-1)*2);			//BAUD RATE USART
			UBRR0H = (uint16_t)((F_CPU/BAUD_RATE0/16-1)*2)>>8;

	}

	else
		{
			UBRR0L = (uint16_t)(F_CPU/BAUD_RATE0/16-1);			//BAUD RATE USART
			UBRR0H = (uint16_t)(F_CPU/BAUD_RATE0/16-1)>>8;
		}

	usart_init0();
}

// USART MOD INITIALIZATION BAUD RATE//

void usart0_mod_init(uint8_t baud_rate)
{
	switch (baud_rate)
	{
		case 1:			//2400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/2400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/2400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/2400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/2400/16-1)>>8;
				}
			break;

		case 2:			//4800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/4800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/4800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/4800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/4800/16-1)>>8;
				}
			break;

		case 3:			//9600
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/9600/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/9600/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/9600/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/9600/16-1)>>8;
				}
			break;

		case 4:			//14400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/14400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/14400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/14400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/14400/16-1)>>8;
				}
			break;

		case 5:			//19200
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/19200/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/19200/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/19200/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/19200/16-1)>>8;
				}
			break;

		case 6:			//28800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/28800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/28800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/28800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/28800/16-1)>>8;
				}
			break;

		case 7:			//38400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/38400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/38400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/38400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/38400/16-1)>>8;
				}
			break;

		case 8:			//57600
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/57600/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/57600/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/57600/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/57600/16-1)>>8;
				}
			break;

		case 9:			//76800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/76800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/76800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/76800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/76800/16-1)>>8;
				}
			break;

		case 10:		//115200
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/115200/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/115200/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/115200/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/115200/16-1)>>8;
				}
			break;

		case 11:		//230400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/230400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/230400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/230400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/230400/16-1)>>8;
				}
			break;

	}


	usart_init0();
}


// USART INITIALIZATION //
void usart_init0()
{

	uint8_t status=0;

	#if RX_BUFFER_SIZE0

		UCSR0B|=(1<<RXEN0)|(1<<RXCIE0);
		
	#endif

	#if TX_BUFFER_SIZE0

		UCSR0B|=(1<<TXEN0);

	#endif

	status=(0<<UMSEL01)|(0<<UMSEL00);


//SELECT CHARTER SIZE //
		if(CHARTER_SIZE0==9)
		{
			UCSR0B|=_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}

		if(CHARTER_SIZE0==8)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}


		if(CHARTER_SIZE0==7)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status&=~_BV(UCSZ00);

		}

		
		if(CHARTER_SIZE0==6)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status&=~_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}

		if(CHARTER_SIZE0==5)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status&=~_BV(UCSZ01);
			  status&=~_BV(UCSZ00);

		}


//SELECT PARITY MODE //

	if((PARITY_MODE0=='O') || (PARITY_MODE0=='o'))
		{
			status|=	_BV(UPM00);
			status|= _BV(UPM01);

		}

	if((PARITY_MODE0=='E') || (PARITY_MODE0=='e'))
		{
			status&=	~_BV(UPM00);
			status|= _BV(UPM01);
			

		}
	
	if((PARITY_MODE0=='N') || (PARITY_MODE0=='n'))
		{
			status&=	~_BV(UPM00);
			status&= ~_BV(UPM01);

		}

	
//SELECT STOP BIT //

	if(STOP_BIT0==1)
	{
		status&=~_BV(USBS0);

	}

	if(STOP_BIT0==2)
	{
		status|=_BV(USBS0);

	}


	UCSR0C=status;

}

////////////////////////////////////////////////////////////////////////////////////////


void usart0_write(uint8_t byte)
{

	if(tx_counter_index0==TX_BUFFER_SIZE0) tx_counter_index0=0;

	tx_buffer0[tx_counter_index0]=byte;

	tx_counter_index0++;


	UCSR0B |= (1<<UDRIE0);
}

ISR(USART_UDRE_vect)
{

	if(tx_wr_counter_index0==TX_BUFFER_SIZE0) tx_wr_counter_index0=0;

	if(tx_wr_counter_index0==tx_counter_index0)
	{
		UCSR0B &=~(1<<UDRIE0);
	}
		else
		{
			UDR0=tx_buffer0[tx_wr_counter_index0];
			tx_wr_counter_index0++;
		}
	
}


ISR(USART_RX_vect)
{
	
	if(rx_counter_index0==RX_BUFFER_SIZE0) rx_counter_index0=0;

	rx_buffer0[rx_counter_index0]=UDR0;
	rx_counter_index0++;

	rx_status0=0;
	

}


uint8_t usart0_read()
{

	if(rx_rd_counter_index0==RX_BUFFER_SIZE0) rx_rd_counter_index0=0;

	if(rx_rd_counter_index0==rx_counter_index0)
	{
		rx_status0=3;

		return 0;
	}
		else
		{

			uint8_t byte=rx_buffer0[rx_rd_counter_index0];
			rx_rd_counter_index0++;

			rx_status0=2;

			return byte;
		}

}


uint8_t usart0_rx_len()
{

	uint8_t len = rx_counter_index0 - rx_rd_counter_index0;
	
	return len;

}


uint8_t rx_error0()
{

rx_status0=1;

return 1;

}

//////////////////////////////////////////////////////////////////////////////////

void usart0_clear_tx_buffer()
{
	tx_wr_counter_index0=0;
	tx_counter_index0=0;
}


void usart0_clear_rx_buffer()
{
	rx_rd_counter_index0=0;
	rx_counter_index0=0;
}

uint8_t  usart0_busy_wait(void)
{
	return (UCSR0B & (1<<UDRIE0));
}

#endif



#if defined (__AVR_ATmega8__) || (__AVR_ATmega16__) || (__AVR_ATmega32__) //**********

// USART INITIALIZATION BAUD RATE//
void usart0_init()
{

	if(u2x0)
	{

			UBRRL = (uint16_t)((F_CPU/BAUD_RATE0/16-1)*2);			//BAUD RATE USART
			UBRRH = (uint16_t)((F_CPU/BAUD_RATE0/16-1)*2)>>8;

	}

	else
		{
			UBRRL = (uint16_t)(F_CPU/BAUD_RATE0/16-1);			//BAUD RATE USART
			UBRRH = (uint16_t)(F_CPU/BAUD_RATE0/16-1)>>8;
		}

	usart_init0();
}

// USART MOD INITIALIZATION BAUD RATE//

void usart0_mod_init(uint8_t baud_rate)
{

	switch (baud_rate)
	{
		case 1:			//2400
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/2400/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/2400/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/2400/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/2400/16-1)>>8;
				}
			break;

		case 2:			//4800
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/4800/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/4800/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/4800/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/4800/16-1)>>8;
				}
			break;

		case 3:			//9600
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/9600/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/9600/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/9600/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/9600/16-1)>>8;
				}
			break;

		case 4:			//14400
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/14400/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/14400/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/14400/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/14400/16-1)>>8;
				}
			break;

		case 5:			//19200
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/19200/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/19200/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/19200/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/19200/16-1)>>8;
				}
			break;

		case 6:			//28800
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/28800/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/28800/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/28800/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/28800/16-1)>>8;
				}
			break;

		case 7:			//38400
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/38400/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/38400/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/38400/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/38400/16-1)>>8;
				}
			break;

		case 8:			//57600
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/57600/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/57600/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/57600/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/57600/16-1)>>8;
				}
			break;

		case 9:			//76800
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/76800/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/76800/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/76800/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/76800/16-1)>>8;
				}
			break;

		case 10:		//115200
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/115200/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/115200/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/115200/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/115200/16-1)>>8;
				}
			break;

		case 11:		//230400
			if(u2x0)
			{

				UBRRL = (uint16_t)((F_CPU/230400/16-1)*2);			//BAUD RATE USART
				UBRRH = (uint16_t)((F_CPU/230400/16-1)*2)>>8;

				}
					else
				{
					UBRRL = (uint16_t)(F_CPU/230400/16-1);			//BAUD RATE USART
					UBRRH = (uint16_t)(F_CPU/230400/16-1)>>8;
				}
			break;

	}


	usart_init0();
}

// USART INITIALIZATION //
void usart_init0()
{
	uint8_t status=0;

	#if RX_BUFFER_SIZE0

		UCSRB=(1<<RXEN)|(1<<RXCIE);
		
	#endif

	#if TX_BUFFER_SIZE0

		UCSRB|=(1<<TXEN);

	#endif

	status=(1<<URSEL);

	//SELECT CHARTER SIZE //
		if(CHARTER_SIZE0==9)
		{
			UCSRB|=_BV(UCSZ2);
			 status|=_BV(UCSZ1);
			  status|=_BV(UCSZ0);

		}

		if(CHARTER_SIZE0==8)
		{
			UCSRB&=~_BV(UCSZ2);
			 status|=_BV(UCSZ1);
			  status|=_BV(UCSZ0);

		}


		if(CHARTER_SIZE0==7)
		{
			UCSRB&=~_BV(UCSZ2);
			 status|=_BV(UCSZ1);
			  status&=~_BV(UCSZ0);

		}

		
		if(CHARTER_SIZE0==6)
		{
			UCSRB&=~_BV(UCSZ2);
			 status&=~_BV(UCSZ1);
			  status|=_BV(UCSZ0);

		}

		if(CHARTER_SIZE0==5)
		{
			UCSRB&=~_BV(UCSZ2);
			 status&=~_BV(UCSZ1);
			  status&=~_BV(UCSZ0);

		}


//SELECT PARITY MODE //

	if((PARITY_MODE0=='O') | (PARITY_MODE0=='o'))
		{
			status|=	_BV(UPM0);
			status|= _BV(UPM1);

		}

	if((PARITY_MODE0=='E') | (PARITY_MODE0=='e'))
		{
			status&=	~_BV(UPM0);
			status|= _BV(UPM1);
			

		}
	
	if((PARITY_MODE0=='N') | (PARITY_MODE0=='n'))
		{
			status&=	~_BV(UPM0);
			status&= ~_BV(UPM1);

		}

	
//SELECT STOP BIT //

	if(STOP_BIT0==1)
	{
		status&=~_BV(USBS);

	}

	if(STOP_BIT0==2)
	{
		status|=_BV(USBS);

	}



	UCSRC=status;

}

////////////////////////////////////////////////////////////////////////////////////////

void usart0_write(uint8_t byte)
{

	if(tx_counter_index0==TX_BUFFER_SIZE0) tx_counter_index0=0;

	tx_buffer0[tx_counter_index0]=byte;

	tx_counter_index0++;


	UCSRB |= (1<<UDRIE);
}

ISR(USART_UDRE_vect)
{

	if(tx_wr_counter_index0==TX_BUFFER_SIZE0) tx_wr_counter_index0=0;

	if(tx_wr_counter_index0==tx_counter_index0)
	{
		UCSRB &=~(1<<UDRIE);

	}
		else
		{
			UDR=tx_buffer0[tx_wr_counter_index0];
			tx_wr_counter_index0++;
		}
	
}


ISR(USART_RXC_vect)
{
	
	if(rx_counter_index0==RX_BUFFER_SIZE0) rx_counter_index0=0;

	rx_buffer0[rx_counter_index0]=UDR;
	rx_counter_index0++;

	rx_status0=0;
	
}

uint8_t usart0_read()
{

	if(rx_rd_counter_index0==RX_BUFFER_SIZE0) rx_rd_counter_index0=0;

	if(rx_rd_counter_index0==rx_counter_index0)
	{
		rx_status0=3;

		return 0;
	}
		else
		{

			uint8_t byte=rx_buffer0[rx_rd_counter_index0];
			rx_rd_counter_index0++;

			rx_status0=2;

			return byte;
		}

}


uint8_t usart0_rx_len()
{

		uint16_t len = rx_counter_index0 - rx_rd_counter_index0;
		return len;
}


uint8_t rx_error0()
{

rx_status0=1;

return 1;

}




void usart0_clear_tx_buffer()
{
	tx_wr_counter_index0=0;
	tx_counter_index0=0;

}


void usart0_clear_rx_buffer()
{
	rx_rd_counter_index0=0;
	rx_counter_index0=0;

}


uint8_t usart0_busy_wait(void)
{
	return (UCSRB & (1<<UDRIE));
}


#endif


#if defined (__AVR_ATmega162__) //***************************************************


// USART INITIALIZATION //
void usart0_init()
{

	if(u2x0)
	{

			UBRR0L = (uint16_t)((F_CPU/BAUD_RATE0/16-1)*2);			//BAUD RATE USART
			UBRR0H = (uint16_t)((F_CPU/BAUD_RATE0/16-1)*2)>>8;

	}

	else
		{
			UBRR0L = (uint16_t)(F_CPU/BAUD_RATE0/16-1);			//BAUD RATE USART
			UBRR0H = (uint16_t)(F_CPU/BAUD_RATE0/16-1)>>8;
		}

	usart_init0();
}


// USART MOD INITIALIZATION BAUD RATE//

void usart0_mod_init(uint8_t baud_rate)
{
	switch (baud_rate)
	{
		case 1:			//2400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/2400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/2400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/2400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/2400/16-1)>>8;
				}
			break;

		case 2:			//4800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/4800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/4800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/4800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/4800/16-1)>>8;
				}
			break;

		case 3:			//9600
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/9600/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/9600/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/9600/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/9600/16-1)>>8;
				}
			break;

		case 4:			//14400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/14400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/14400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/14400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/14400/16-1)>>8;
				}
			break;

		case 5:			//19200
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/19200/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/19200/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/19200/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/19200/16-1)>>8;
				}
			break;

		case 6:			//28800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/28800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/28800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/28800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/28800/16-1)>>8;
				}
			break;

		case 7:			//38400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/38400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/38400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/38400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/38400/16-1)>>8;
				}
			break;

		case 8:			//57600
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/57600/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/57600/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/57600/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/57600/16-1)>>8;
				}
			break;

		case 9:			//76800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/76800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/76800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/76800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/76800/16-1)>>8;
				}
			break;

		case 10:		//115200
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/115200/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/115200/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/115200/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/115200/16-1)>>8;
				}
			break;

		case 11:		//230400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/230400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/230400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/230400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/230400/16-1)>>8;
				}
			break;

	}


	usart_init0();
}


// USART INITIALIZATION //

void usart_init0()
{

	uint8_t status=0;

	#if RX_BUFFER_SIZE0

		UCSR0B|=(1<<RXEN0)|(1<<RXCIE0);
		
	#endif

	#if TX_BUFFER_SIZE0

		UCSR0B|=(1<<TXEN0);

	#endif

	status=(1<<URSEL0);


	//SELECT CHARTER SIZE //
		if(CHARTER_SIZE0==9)
		{
			UCSR0B|=_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}

		if(CHARTER_SIZE0==8)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}


		if(CHARTER_SIZE0==7)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status&=~_BV(UCSZ00);

		}

		
		if(CHARTER_SIZE0==6)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status&=~_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}

		if(CHARTER_SIZE0==5)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status&=~_BV(UCSZ01);
			  status&=~_BV(UCSZ00);

		}


//SELECT PARITY MODE //

	if((PARITY_MODE0=='O') | (PARITY_MODE0=='o'))
		{
			status|=	_BV(UPM00);
			status|= _BV(UPM01);

		}

	if((PARITY_MODE0=='E') | (PARITY_MODE0=='e'))
		{
			status&=	~_BV(UPM00);
			status|= _BV(UPM01);
			

		}
	
	if((PARITY_MODE0=='N') | (PARITY_MODE0=='n'))
		{
			status&=	~_BV(UPM00);
			status&= ~_BV(UPM01);

		}

	
//SELECT STOP BIT //

	if(STOP_BIT0==1)
	{
		status&=~_BV(USBS0);

	}

	if(STOP_BIT0==2)
	{
		status|=_BV(USBS0);

	}


		UCSR0C=status;


}

////////////////////////////////////////////////////////////////////////////////////////

void usart1_init()
{

	if(u2x1)
	{

			UBRR1L = (uint16_t)((F_CPU/BAUD_RATE1/16-1)*2);			//BAUD RATE USART
			UBRR1H = (uint16_t)((F_CPU/BAUD_RATE1/16-1)*2)>>8;

	}

	else
		{
			UBRR1L = (uint16_t)(F_CPU/BAUD_RATE1/16-1);			//BAUD RATE USART
			UBRR1H = (uint16_t)(F_CPU/BAUD_RATE1/16-1)>>8;
		}

	usart_init1();
}

// USART MOD INITIALIZATION BAUD RATE//

void usart1_mod_init(uint8_t baud_rate)
{
	switch (baud_rate)
	{
		case 1:			//2400
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/2400/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/2400/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/2400/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/2400/16-1)>>8;
				}
			break;

		case 2:			//4800
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/4800/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/4800/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/4800/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/4800/16-1)>>8;
				}
			break;

		case 3:			//9600
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/9600/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/9600/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/9600/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/9600/16-1)>>8;
				}
			break;

		case 4:			//14400
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/14400/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/14400/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/14400/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/14400/16-1)>>8;
				}
			break;

		case 5:			//19200
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/19200/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/19200/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/19200/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/19200/16-1)>>8;
				}
			break;

		case 6:			//28800
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/28800/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/28800/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/28800/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/28800/16-1)>>8;
				}
			break;

		case 7:			//38400
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/38400/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/38400/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/38400/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/38400/16-1)>>8;
				}
			break;

		case 8:			//57600
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/57600/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/57600/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/57600/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/57600/16-1)>>8;
				}
			break;

		case 9:			//76800
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/76800/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/76800/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/76800/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/76800/16-1)>>8;
				}
			break;

		case 10:		//115200
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/115200/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/115200/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/115200/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/115200/16-1)>>8;
				}
			break;

		case 11:		//230400
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/230400/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/230400/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/230400/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/230400/16-1)>>8;
				}
			break;

	}


	usart_init1();
}


// USART INITIALIZATION //

void usart_init1()
{

	uint8_t status=0;

	#if RX_BUFFER_SIZE1

		UCSR1B|=(1<<RXEN1)|(1<<RXCIE1);
		
	#endif

	#if TX_BUFFER_SIZE1

		UCSR1B|=(1<<TXEN1);

	#endif

	status=(1<<URSEL1);


	//SELECT CHARTER SIZE //
		if(CHARTER_SIZE1==9)
		{
			UCSR1B|=_BV(UCSZ12);
			 status|=_BV(UCSZ11);
			  status|=_BV(UCSZ10);

		}

		if(CHARTER_SIZE1==8)
		{
			UCSR1B&=~_BV(UCSZ12);
			 status|=_BV(UCSZ11);
			  status|=_BV(UCSZ10);

		}


		if(CHARTER_SIZE1==7)
		{
			UCSR1B&=~_BV(UCSZ12);
			 status|=_BV(UCSZ11);
			  status&=~_BV(UCSZ10);

		}

		
		if(CHARTER_SIZE1==6)
		{
			UCSR1B&=~_BV(UCSZ12);
			 status&=~_BV(UCSZ11);
			  status|=_BV(UCSZ10);

		}

		if(CHARTER_SIZE0==5)
		{
			UCSR1B&=~_BV(UCSZ12);
			 status&=~_BV(UCSZ11);
			  status&=~_BV(UCSZ10);

		}


	//SELECT PARITY MODE //

	if((PARITY_MODE1=='O') | (PARITY_MODE1=='o'))
		{
			status|=	_BV(UPM10);
			status|= _BV(UPM11);

		}

	if((PARITY_MODE1=='E') | (PARITY_MODE1=='e'))
		{
			status&=	~_BV(UPM10);
			status|= _BV(UPM11);
			

		}
	
	if((PARITY_MODE1=='N') | (PARITY_MODE1=='n'))
		{
			status&=	~_BV(UPM10);
			status&= ~_BV(UPM11);

		}

	
//SELECT STOP BIT //

	if(STOP_BIT1==1)
	{
		status&=~_BV(USBS1);

	}

	if(STOP_BIT1==2)
	{
		status|=_BV(USBS1);

	}


		UCSR1C=status;

}

////////////////////////////////////////////////////////////////////////////////////

void usart0_write(uint8_t byte)
{

	if(tx_counter_index0==TX_BUFFER_SIZE0) tx_counter_index0=0;

	tx_buffer0[tx_counter_index0]=byte;

	tx_counter_index0++;

	UCSR0B |= (1<<UDRIE0);
}

ISR(USART0_UDRE_vect)
{

	if(tx_wr_counter_index0==TX_BUFFER_SIZE0) tx_wr_counter_index0=0;

	if(tx_wr_counter_index0==tx_counter_index0)
	{
		UCSR0B &=~(1<<UDRIE0);
	}
		else
		{
			UDR0=tx_buffer0[tx_wr_counter_index0];
			tx_wr_counter_index0++;
		}
	
}


ISR(USART0_RXC_vect)
{
	
	
	if(rx_counter_index0==RX_BUFFER_SIZE0) rx_counter_index0=0;

	rx_buffer0[rx_counter_index0]=UDR0;
	rx_counter_index0++;

	rx_status0=0;
	

}

uint8_t usart0_read()
{

	if(rx_rd_counter_index0==RX_BUFFER_SIZE0) rx_rd_counter_index0=0;

	if(rx_rd_counter_index0==rx_counter_index0)
	{
		rx_status0=3;

		return 0;
	}
		else
		{

			uint8_t byte=rx_buffer0[rx_rd_counter_index0];
			rx_rd_counter_index0++;

			rx_status0=2;

			return byte;
		}

}


uint8_t usart0_rx_len()
{

uint8_t len = rx_counter_index0 - rx_rd_counter_index0;
	
	return len;

}


uint8_t rx_error0()
{

rx_status0=1;

return 1;

}

//////////////////////////////////////////////////////////////////////////////////

void usart1_write(uint8_t byte)
{

	if(tx_counter_index1==TX_BUFFER_SIZE1) tx_counter_index1=0;

	tx_buffer1[tx_counter_index1]=byte;

	tx_counter_index1++;

	UCSR1B |= (1<<UDRIE1);
}

ISR(USART1_UDRE_vect)
{

	if(tx_wr_counter_index1==TX_BUFFER_SIZE1) tx_wr_counter_index1=0;

	if(tx_wr_counter_index1==tx_counter_index1)
	{
		UCSR1B &=~(1<<UDRIE1);
	}
		else
		{
			UDR1=tx_buffer1[tx_wr_counter_index1];
			tx_wr_counter_index1++;
		}
	
}


ISR(USART1_RXC_vect)
{
		
	if(rx_counter_index1==RX_BUFFER_SIZE1) rx_counter_index1=0;

	rx_buffer1[rx_counter_index1]=UDR1;
	rx_counter_index1++;

	rx_status1=0;

}

uint8_t usart1_read()
{

	if(rx_rd_counter_index1==RX_BUFFER_SIZE1) rx_rd_counter_index1=0;

	if(rx_rd_counter_index1==rx_counter_index1)
	{
		rx_status1=3;

		return 0;
	}
		else
		{

			uint8_t byte=rx_buffer1[rx_rd_counter_index1];
			rx_rd_counter_index1++;

			rx_status1=2;

			return byte;
		}

}


uint8_t usart1_rx_len()
{

uint8_t len = rx_counter_index1 - rx_rd_counter_index1;
	
	return len;

}


uint8_t rx_error1()
{

rx_status1=1;

return 1;

}



void usart0_clear_tx_buffer()
{
	tx_counter_index0=0;
	tx_wr_counter_index0=0;

}

void usart1_clear_tx_buffer()
{
	tx_wr_counter_index1=0;
	tx_counter_index1=0;

}


void usart0_clear_rx_buffer()
{
	rx_rd_counter_index0=0;
	rx_counter_index0=0;

}

void usart1_clear_rx_buffer()
{
	rx_rd_counter_index1=0;
	rx_counter_index1=0;

}

void usart1_write_str(char *pData_Usart1)
{
	while(usart1_busy_wait());

	uint16_t i=0;

	while(pData_Usart1[i]!=0)
	{
		usart1_write(pData_Usart1[i]);

		if(pData_Usart1[i]=='\n')
		{
			_delay_ms(USART1_DELAY_MS);
			usart1_write('\r');
		}

		i++;

		_delay_ms(USART1_DELAY_MS);
	}
	
}


uint8_t usart0_busy_wait(void)
{
	return (UCSR0B & (1<<UDRIE0));
}

uint8_t usart1_busy_wait(void)
{
	return (UCSR1B & (1<<UDRIE1));
}


#endif




#if defined (__AVR_ATmega128__) //**************************************************


// USART INITIALIZATION //
void usart0_init()
{

	if(u2x0)
	{

			UBRR0L = (uint16_t)((F_CPU/BAUD_RATE0/16-1)*2);			//BAUD RATE USART
			UBRR0H = (uint16_t)((F_CPU/BAUD_RATE0/16-1)*2)>>8;

	}

	else
		{
			UBRR0L = (uint16_t)(F_CPU/BAUD_RATE0/16-1);			//BAUD RATE USART
			UBRR0H = (uint16_t)(F_CPU/BAUD_RATE0/16-1)>>8;
		}

	usart_init0();
}


// USART MOD INITIALIZATION BAUD RATE//

void usart0_mod_init(uint8_t baud_rate)
{
	switch (baud_rate)
	{
		case 1:			//2400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/2400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/2400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/2400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/2400/16-1)>>8;
				}
			break;

		case 2:			//4800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/4800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/4800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/4800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/4800/16-1)>>8;
				}
			break;

		case 3:			//9600
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/9600/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/9600/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/9600/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/9600/16-1)>>8;
				}
			break;

		case 4:			//14400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/14400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/14400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/14400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/14400/16-1)>>8;
				}
			break;

		case 5:			//19200
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/19200/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/19200/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/19200/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/19200/16-1)>>8;
				}
			break;

		case 6:			//28800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/28800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/28800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/28800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/28800/16-1)>>8;
				}
			break;

		case 7:			//38400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/38400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/38400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/38400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/38400/16-1)>>8;
				}
			break;

		case 8:			//57600
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/57600/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/57600/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/57600/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/57600/16-1)>>8;
				}
			break;

		case 9:			//76800
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/76800/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/76800/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/76800/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/76800/16-1)>>8;
				}
			break;

		case 10:		//115200
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/115200/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/115200/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/115200/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/115200/16-1)>>8;
				}
			break;

		case 11:		//230400
			if(u2x0)
			{

				UBRR0L = (uint16_t)((F_CPU/230400/16-1)*2);			//BAUD RATE USART
				UBRR0H = (uint16_t)((F_CPU/230400/16-1)*2)>>8;

				}
					else
				{
					UBRR0L = (uint16_t)(F_CPU/230400/16-1);			//BAUD RATE USART
					UBRR0H = (uint16_t)(F_CPU/230400/16-1)>>8;
				}
			break;

	}


	usart_init0();
}


// USART INITIALIZATION //

void usart_init0()
{
	uint8_t status=0;

	#if RX_BUFFER_SIZE0

		UCSR0B|=(1<<RXEN0)|(1<<RXCIE0);
		
	#endif

	#if TX_BUFFER_SIZE0

		UCSR0B|=(1<<TXEN0);

	#endif

	//UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0);

	//status=(1<<UMSEL0);

	//SELECT CHARTER SIZE //
		if(CHARTER_SIZE0==9)
		{
			UCSR0B|=_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}

		if(CHARTER_SIZE0==8)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}


		if(CHARTER_SIZE0==7)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status|=_BV(UCSZ01);
			  status&=~_BV(UCSZ00);

		}

		
		if(CHARTER_SIZE0==6)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status&=~_BV(UCSZ01);
			  status|=_BV(UCSZ00);

		}

		if(CHARTER_SIZE0==5)
		{
			UCSR0B&=~_BV(UCSZ02);
			 status&=~_BV(UCSZ01);
			  status&=~_BV(UCSZ00);

		}


//SELECT PARITY MODE //

	if((PARITY_MODE0=='O') | (PARITY_MODE0=='o'))
		{
			status|=	_BV(UPM00);
			status|= _BV(UPM01);

		}

	if((PARITY_MODE0=='E') | (PARITY_MODE0=='e'))
		{
			status&=	~_BV(UPM00);
			status|= _BV(UPM01);
			

		}
	
	if((PARITY_MODE0=='N') | (PARITY_MODE0=='n'))
		{
			status&=	~_BV(UPM00);
			status&= ~_BV(UPM01);

		}

	
//SELECT STOP BIT //

	if(STOP_BIT0==1)
	{
		status&=~_BV(USBS0);

	}

	if(STOP_BIT0==2)
	{
		status|=_BV(USBS0);

	}


		UCSR0C=status;

}

////////////////////////////////////////////////////////////////////////////////////////

void usart1_init()
{

	if(u2x1)
	{

			UBRR1L = (uint16_t)((F_CPU/BAUD_RATE1/16-1)*2);			//BAUD RATE USART
			UBRR1H = (uint16_t)((F_CPU/BAUD_RATE1/16-1)*2)>>8;

	}

	else
		{
			UBRR1L = (uint16_t)(F_CPU/BAUD_RATE1/16-1);			//BAUD RATE USART
			UBRR1H = (uint16_t)(F_CPU/BAUD_RATE1/16-1)>>8;
		}

	usart_init1();
}

// USART MOD INITIALIZATION BAUD RATE//

void usart1_mod_init(uint8_t baud_rate)
{
	switch (baud_rate)
	{
		case 1:			//2400
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/2400/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/2400/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/2400/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/2400/16-1)>>8;
				}
			break;

		case 2:			//4800
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/4800/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/4800/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/4800/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/4800/16-1)>>8;
				}
			break;

		case 3:			//9600
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/9600/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/9600/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/9600/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/9600/16-1)>>8;
				}
			break;

		case 4:			//14400
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/14400/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/14400/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/14400/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/14400/16-1)>>8;
				}
			break;

		case 5:			//19200
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/19200/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/19200/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/19200/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/19200/16-1)>>8;
				}
			break;

		case 6:			//28800
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/28800/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/28800/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/28800/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/28800/16-1)>>8;
				}
			break;

		case 7:			//38400
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/38400/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/38400/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/38400/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/38400/16-1)>>8;
				}
			break;

		case 8:			//57600
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/57600/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/57600/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/57600/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/57600/16-1)>>8;
				}
			break;

		case 9:			//76800
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/76800/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/76800/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/76800/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/76800/16-1)>>8;
				}
			break;

		case 10:		//115200
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/115200/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/115200/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/115200/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/115200/16-1)>>8;
				}
			break;

		case 11:		//230400
			if(u2x1)
			{

				UBRR1L = (uint16_t)((F_CPU/230400/16-1)*2);			//BAUD RATE USART
				UBRR1H = (uint16_t)((F_CPU/230400/16-1)*2)>>8;

				}
					else
				{
					UBRR1L = (uint16_t)(F_CPU/230400/16-1);			//BAUD RATE USART
					UBRR1H = (uint16_t)(F_CPU/230400/16-1)>>8;
				}
			break;

	}


	usart_init1();
}


// USART INITIALIZATION //

void usart_init1()
{

	uint8_t status=0;

	#if RX_BUFFER_SIZE0

		UCSR1B|=(1<<RXEN1)|(1<<RXCIE1);
		
	#endif

	#if TX_BUFFER_SIZE0

		UCSR1B|=(1<<TXEN1);

	#endif

	//UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1)|(0<<TXCIE1)|(0<<UDRIE1);

	//SELECT CHARTER SIZE //
		if(CHARTER_SIZE1==9)
		{
			UCSR1B|=_BV(UCSZ12);
			 status|=_BV(UCSZ11);
			  status|=_BV(UCSZ10);

		}

		if(CHARTER_SIZE1==8)
		{
			UCSR1B&=~_BV(UCSZ12);
			 status|=_BV(UCSZ11);
			  status|=_BV(UCSZ10);

		}


		if(CHARTER_SIZE1==7)
		{
			UCSR1B&=~_BV(UCSZ12);
			 status|=_BV(UCSZ11);
			  status&=~_BV(UCSZ10);

		}

		
		if(CHARTER_SIZE1==6)
		{
			UCSR1B&=~_BV(UCSZ12);
			 status&=~_BV(UCSZ11);
			  status|=_BV(UCSZ10);

		}

		if(CHARTER_SIZE0==5)
		{
			UCSR1B&=~_BV(UCSZ12);
			 status&=~_BV(UCSZ11);
			  status&=~_BV(UCSZ10);

		}


	//SELECT PARITY MODE //

	if((PARITY_MODE1=='O') | (PARITY_MODE1=='o'))
		{
			status|=	_BV(UPM10);
			status|= _BV(UPM11);

		}

	if((PARITY_MODE1=='E') | (PARITY_MODE1=='e'))
		{
			status&=	~_BV(UPM10);
			status|= _BV(UPM11);
			

		}
	
	if((PARITY_MODE1=='N') | (PARITY_MODE1=='n'))
		{
			status&=	~_BV(UPM10);
			status&= ~_BV(UPM11);

		}

	
//SELECT STOP BIT //

	if(STOP_BIT1==1)
	{
		status&=~_BV(USBS1);

	}

	if(STOP_BIT1==2)
	{
		status|=_BV(USBS1);

	}


		UCSR1C=status;


}

////////////////////////////////////////////////////////////////////////////////////

void usart0_write(uint8_t byte)
{

	if(tx_counter_index0==TX_BUFFER_SIZE0) tx_counter_index0=0;

	tx_buffer0[tx_counter_index0]=byte;

	tx_counter_index0++;

	UCSR0B |= (1<<UDRIE0);
}

ISR(USART0_UDRE_vect)
{

	if(tx_wr_counter_index0==TX_BUFFER_SIZE0) tx_wr_counter_index0=0;

	if(tx_wr_counter_index0==tx_counter_index0)
	{
		UCSR0B &=~(1<<UDRIE0);
	}
		else
		{
			UDR0=tx_buffer0[tx_wr_counter_index0];
			tx_wr_counter_index0++;
		}
	
}


ISR(USART0_RX_vect)
{
	
	if(rx_counter_index0==RX_BUFFER_SIZE0) rx_counter_index0=0;

	rx_buffer0[rx_counter_index0]=UDR0;
	rx_counter_index0++;

	rx_status0=0;

}

uint8_t usart0_read()
{

	if(rx_rd_counter_index0==RX_BUFFER_SIZE0) rx_rd_counter_index0=0;

	if(rx_rd_counter_index0==rx_counter_index0)
	{
		rx_status0=3;

		return 0;
	}
		else
		{

			uint8_t byte=rx_buffer0[rx_rd_counter_index0];
			rx_rd_counter_index0++;

			rx_status0=2;

			return byte;
		}

}


uint8_t usart0_rx_len()
{

uint8_t len = rx_counter_index0 - rx_rd_counter_index0;
	
	return len;

}


uint8_t rx_error0()
{

rx_status0=1;

return 1;

}

//////////////////////////////////////////////////////////////////////////////////

void usart1_write(uint8_t byte)
{

	if(tx_counter_index1==TX_BUFFER_SIZE1) tx_counter_index1=0;

	tx_buffer1[tx_counter_index1]=byte;

	tx_counter_index1++;

	UCSR1B |= (1<<UDRIE1);
}

ISR(USART1_UDRE_vect)
{

	if(tx_wr_counter_index1==TX_BUFFER_SIZE1) tx_wr_counter_index1=0;

	if(tx_wr_counter_index1==tx_counter_index1)
	{
		UCSR1B &=~(1<<UDRIE1);
	}
		else
		{
			UDR1=tx_buffer1[tx_wr_counter_index1];
			tx_wr_counter_index1++;
		}
	
}


ISR(USART1_RX_vect)
{

	if(rx_counter_index1==RX_BUFFER_SIZE1) rx_counter_index1=0;

	rx_buffer1[rx_counter_index1]=UDR1;
	rx_counter_index1++;

	rx_status1=0;

}

uint8_t usart1_read()
{

	if(rx_rd_counter_index1==RX_BUFFER_SIZE1) rx_rd_counter_index1=0;

	if(rx_rd_counter_index1==rx_counter_index1)
	{
		rx_status1=3;

		return 0;
	}
		else
		{

			uint8_t byte=rx_buffer1[rx_rd_counter_index1];
			rx_rd_counter_index1++;

			rx_status1=2;

			return byte;
		}

}


uint8_t usart1_rx_len()
{

uint8_t len = rx_counter_index1 - rx_rd_counter_index1;
	
	return len;

}


uint8_t rx_error1()
{

rx_status1=1;

return 1;

}



void usart0_clear_tx_buffer()
{
	tx_counter_index0=0;
	tx_wr_counter_index0=0;

}

void usart1_clear_tx_buffer()
{
	tx_wr_counter_index1=0;
	tx_counter_index1=0;

}


void usart0_clear_rx_buffer()
{
	rx_rd_counter_index0=0;
	rx_counter_index0=0;

}

void usart1_clear_rx_buffer()
{
	rx_rd_counter_index1=0;
	rx_counter_index1=0;

}




void usart1_write_str(char *pData_Usart1)
{
	while(usart1_busy_wait());

	uint16_t i=0;

	while(pData_Usart1[i]!=0)
	{
		usart1_write(pData_Usart1[i]);

		if(pData_Usart1[i]=='\n')
		{
			_delay_ms(USART1_DELAY_MS);
			usart1_write('\r');
		}

		i++;

		_delay_ms(USART1_DELAY_MS);
	}
	
}


uint8_t usart0_busy_wait(void)
{
	return (UCSR0B & (1<<UDRIE0));
}

uint8_t usart1_busy_wait(void)
{
	return (UCSR1B & (1<<UDRIE1));
}


#endif
