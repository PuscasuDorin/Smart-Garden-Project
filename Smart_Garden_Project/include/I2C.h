
#ifndef I2C_H_
#define I2C_H_

	# define F_CPU 16000000UL

	void I2C_init(void);
	
	void I2C_Start(void);
	
	void I2C_Stop(void);
	
	void I2C_Write(uint8_t data);
	
	void I2C_LCD_Write(uint8_t lcd_address, uint8_t control_byte ,uint8_t data);

#endif /* I2C_H_ */