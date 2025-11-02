#define F_CPU 16000000UL

#include <avr/io.h>
#include "ADC.h"
#include <util/delay.h>


void ADC_init(void){
	
	ADMUX |= (1<<REFS0);
	
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS2);
}

uint16_t ADC_read(uint8_t channel){

	if (channel < 8) {
		ADCSRB &= ~(1 << MUX5);
		} else {
		ADCSRB |= (1 << MUX5);
		channel -= 8;
	}
	ADMUX = (1<<REFS0) | (channel & 0x0F);
	_delay_us(50);
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));
	
	return ADC;
}

float ADC_read_voltage(uint8_t channel ,uint8_t V_ref){
	
	float ADC_val = ADC_read(channel);
	float ADC_voltage = (ADC_val * V_ref)/1024;
	
	return ADC_voltage;
}