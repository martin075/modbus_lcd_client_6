# modbus_lcd_client_6
modbus client with LCD HD44780, 6xDS18B20, RS485, BMP180, ATmega328P<br /> 
### modbus address 
		0-5 temperature sensors - DS18B20 
		6 - atmospheric pressure - BMP180 (relative or absolute) 
		7 - temperature from BMP180 
		8 - setting of thermostat1 
		9 - setting of thermostat2 
		10 - setting of delay between reading values 
		11 - correction to sea level (relative press) 