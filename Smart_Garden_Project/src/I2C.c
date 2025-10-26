#include <avr/io.h>
#include "I2C.h"

void I2C_init(void){
	TWSR = 0x00;
	uint32_t scl_frequency = 100000;
	uint8_t twps_val = TWSR & 0x03;
	TWBR = ((F_CPU / scl_frequency) - 16) / (2 * (1 << (2 * twps_val)));
}

void I2C_Start(void){
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	while (!(TWCR & (1<<TWINT)));
}

void I2C_Stop(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void I2C_Write(uint8_t data){
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while (!(TWCR & (1<<TWINT)));
}


