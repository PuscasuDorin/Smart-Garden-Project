
#include <avr/io.h>
#include "ADC.h"

void ADC_init(void){
	
	ADMUX |= (1<<REFS0);
	
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS2);
}

uint16_t ADC_read(uint8_t channel){
	
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