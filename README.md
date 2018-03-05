# modbus_lcd_client_6
modbus client with LCD HD44780, 6 x DS18B20, RS485, BMP180, ATmega328P, 2x relays<br /> 
0-7 address values, 8-13 settings<br />
### modbus address 
		0-5 temperature sensors - DS18B20 
		6 - atmospheric pressure - BMP180 (relative or absolute) 
		7 - temperature from BMP180 
		8 - condition of thermostat1 
		9 - condition of thermostat2 
		10 - value -thermostat1 0-90°C
		11 - value - thermostat2 0-90°C
		12 - setting of delay between reading values 0-100 sec
		13 - correction to sea level (relative press) 0-100 hPa
