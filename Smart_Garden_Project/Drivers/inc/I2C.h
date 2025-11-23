
#ifndef I2C_H_
#define I2C_H_

	# define F_CPU 16000000UL

	void I2C_init(void);
	
	void I2C_start(void);
	
	void I2C_stop(void);
	
	void I2C_write(uint8_t data);
	
	void I2C_LCD_write(uint8_t lcd_address, uint8_t control_byte ,uint8_t data);

#endif /* I2C_H_ */