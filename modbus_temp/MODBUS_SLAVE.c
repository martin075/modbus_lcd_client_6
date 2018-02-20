

	#include "MODBUS_SLAVE.h"


	uint16_t quant_reg;


//0-OK; 1-NOT SLAVE ADDRESS; 2-ERROR; 3-ERROR CRC;//

int modbus_slave(uint8_t slave_id)
{

#if(!(USART_MODBUS))	

	uint8_t Len=usart0_rx_len();

	char Data[Len];

	for(uint8_t i=0; i<sizeof(Data); i++)
		Data[i]=usart0_read();

	usart0_clear_tx_buffer();
	usart0_clear_rx_buffer();

#endif

#if(USART_MODBUS) 
	uint8_t Len=usart1_rx_len();

	char Data[Len];

	for(uint8_t i=0; i<sizeof(Data); i++)
		Data[i]=usart1_read();

	usart1_clear_tx_buffer();
	usart1_clear_rx_buffer();

#endif


	if(Data[0]!=slave_id) return NOT_SLAVE_ID;	//1-NOT SLAVE ADDRESS.

	uint16_t modbus_crc=0xFFFF;

	for(uint16_t i=0; i<(Len-2); i++)
		modbus_crc=_crc16_update(modbus_crc, Data[i]);



	uint8_t modbus_crc_l=modbus_crc>>8;
	uint8_t modbus_crc_h=modbus_crc;

	if((modbus_crc_h!=Data[Len-2]) | (modbus_crc_l!=Data[Len-1])) return ERROR_CRC; // Error CRC.

#ifdef PORT_RS485			
	PORT_RS485|=(1<<RE_DE);
#endif

	uint8_t function=Data[1];

	uint16_t add_reg;

	add_reg=8<<Data[2];
	add_reg=Data[3];

	uint16_t quant_reg;
	quant_reg=8<<Data[4];
	quant_reg=Data[5];

	uint8_t err_addr_reg = 0;

	if(((function==COMMAND_HOLDING_REG) || (function==COMMAND_INPUT_REG)) &&
	  ((add_reg<ADDRES_REG_READ) || (quant_reg>QUANTITY_REG_READ) ||
	  (add_reg+quant_reg)>(ADDRES_REG_READ+QUANTITY_REG_READ)))
	{
		err_addr_reg = 1;
	}
	
	if((function==COMMAND_WRITE_REG) && (((add_reg<ADDRES_REG_WRITE) ||
	  (quant_reg>QUANTITY_REG_WRITE) || (quant_reg>QUANTITY_REG_WRITE) ||
	  (add_reg+quant_reg)>(ADDRES_REG_WRITE+QUANTITY_REG_WRITE))))
	{
		err_addr_reg = 2;
	}

	if(err_addr_reg)
	{
			
		char data_err[5]={slave_id, 0x00, 0x02, 0xFF, 0xFF};
		if( err_addr_reg == 1)
			data_err[1] = 0x83;
		if( err_addr_reg == 2)
			data_err[1] = 0x90;	
			
		uint16_t modbus_crc=0xFFFF;
		for(uint16_t i=0; i<(sizeof(data_err)-2); i++)
			modbus_crc=_crc16_update(modbus_crc, data_err[i]);
			
		data_err[(sizeof(data_err)-2)]=modbus_crc;
		data_err[(sizeof(data_err)-1)]=modbus_crc>>8;

					
		#if(!(USART_MODBUS))
					
			for(uint16_t i=0; i<sizeof(data_err); i++)
			{
				usart0_write(data_err[i]);
				_delay_ms(USART0_DELAY_MS);
			}
											
			while(usart0_busy_wait());
		#endif

		#if(USART_MODBUS) 

			for(uint16_t i=0; i<sizeof(data_err); i++)
			{
				usart1_write(data_err[i]);
				_delay_ms(USART1_DELAY_MS);
			}							
			while(usart1_busy_wait());
		#endif
					
#ifdef PORT_RS485		
					
		_delay_ms(5);

		PORT_RS485&=~(1<<RE_DE);
#endif
			
	return ERROR_ADDR_REG;	//Error Legal Address Registr.

	}

	if((function==COMMAND_HOLDING_REG) || (function==COMMAND_INPUT_REG))
	{
			uint8_t data_tx[5+quant_reg*2];

			for(uint16_t i=0; i<2; i++)
				data_tx[i]=Data[i];	
	

			data_tx[2]=quant_reg*2;


			uint16_t n=add_reg;
			for(uint16_t i=0; n<(quant_reg+add_reg); i+=2)
			{
				data_tx[i+4]=registers[n];
				data_tx[i+3]=registers[n]>>8;

				n++;
			}



			modbus_crc=0xFFFF;
			for(uint16_t i=0; i<(sizeof(data_tx)-2); i++)
				modbus_crc=_crc16_update(modbus_crc, data_tx[i]);
	

	
			data_tx[(sizeof(data_tx)-2)]=modbus_crc;
			data_tx[(sizeof(data_tx)-1)]=modbus_crc>>8;

			#if(!(USART_MODBUS))

			for(uint16_t i=0; i<sizeof(data_tx); i++)
			{
				usart0_write(data_tx[i]);
				_delay_ms(USART0_DELAY_MS);
			}
				while(usart0_busy_wait());
			#endif
					


			#if(USART_MODBUS)

			for(uint16_t i=0; i<sizeof(data_tx); i++)
			{
				usart1_write(data_tx[i]);
				_delay_ms(USART1_DELAY_MS);
			}
				while(usart1_busy_wait());
			#endif
					
#ifdef PORT_RS485		
					
			_delay_ms(5);

			PORT_RS485&=~(1<<RE_DE);

#endif	
		return OK;
	
	}
	
	if(function==COMMAND_WRITE_REG)
	{
	
		uint8_t n=7;
		for(uint16_t i=add_reg; i<(add_reg+quant_reg); i++)
		{
			registers[i]=Data[n]*256;
			registers[i]|=Data[n+1];

			n=n+2;
		}



		uint8_t data_tx[8];

		for(uint16_t i=0; i<(sizeof(data_tx)-2); i++)
		{
			data_tx[i]=Data[i];	
		}

		uint16_t modbus_crc=0xFFFF;
		for(uint16_t i=0; i<(sizeof(data_tx)-2); i++)
			modbus_crc=_crc16_update(modbus_crc, data_tx[i]);
		

		data_tx[(sizeof(data_tx)-2)]=modbus_crc;
		data_tx[(sizeof(data_tx)-1)]=modbus_crc>>8;


		#if(!(USART_MODBUS))

			for(uint16_t i=0; i<sizeof(data_tx); i++)
			{
				usart0_write(data_tx[i]);
				_delay_ms(USART0_DELAY_MS);
			}
			while(usart0_busy_wait());
		#endif
					


		#if(USART_MODBUS)

			for(uint16_t i=0; i<sizeof(data_tx); i++)
			{
				usart1_write(data_tx[i]);
				_delay_ms(USART1_DELAY_MS);
			}
			while(usart1_busy_wait());
		#endif
					
#ifdef PORT_RS485		
					
		_delay_ms(5);

		PORT_RS485&=~(1<<RE_DE);
#endif

		return OK;
	}


	//Ilegal Function********************************///

	char data_err[5]={slave_id, 0x83, 0x01, 0xFF, 0xFF};

	modbus_crc=0xFFFF;
	for(uint16_t i=0; i<(sizeof(data_err)-2); i++)
	{
		modbus_crc=_crc16_update(modbus_crc, data_err[i]);
	}

	data_err[(sizeof(data_err)-2)]=modbus_crc;
	data_err[(sizeof(data_err)-1)]=modbus_crc>>8;

	#if(!(USART_MODBUS))

		for(uint16_t i=0; i<sizeof(data_err); i++)
		{
			usart0_write(data_err[i]);
			_delay_ms(USART0_DELAY_MS);
		}
		while(usart0_busy_wait());
	#endif
					


	#if(USART_MODBUS)

		for(uint16_t i=0; i<sizeof(data_err); i++)
		{
			usart1_write(data_err[i]);
			_delay_ms(USART1_DELAY_MS);
		}
		while(usart1_busy_wait());
	#endif
					
#ifdef PORT_RS485			
	_delay_ms(5);

	PORT_RS485&=~(1<<RE_DE);
#endif

return ERROR_FUNCTION;	


}
