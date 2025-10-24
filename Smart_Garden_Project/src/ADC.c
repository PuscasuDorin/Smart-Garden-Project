
#include <avr/io.h>
#include "ADC.h"

void ADC_init(void){
	
	ADMUX |= (1<<REFS0);
	
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS2);
}

uint16_t ADC_read(uint8_t channel){
	if(channel >= 0 && channel <= 7){
		ADCSRB &= ~(1<<MUX5);
	}
	if(channel > 7 && channel <= 15){
		ADCSRB |= (1<<MUX5);
		
		switch (channel){
			case 8:
				channel = 0;
				break;
			case 9:
				channel = 1;
				break;
			case 10:
				channel = 2;
				break;
			case 11:
				channel = 3;
				break;
			case 12:
				channel = 4;
				break;
			case 13:
				channel = 5;
				break;
			case 14:
				channel = 6;
				break;
			case 15:
				channel = 7;
				break;
		}
	}
	ADMUX |= (ADMUX & 0xF0) | (channel & 0x0F);

	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));
	
	return ADC;
}

float ADC_read_voltage(uint8_t channel ,uint8_t V_ref){
	
	float ADC_val = ADC_read(channel);
	float ADC_voltage = (ADC_val * V_ref)/1024;
	
	return ADC_voltage;
}