#include <avr/io.h>
#include "PWM.h"

void PWM_init (void){
	TCCR0A = (1<<COM0B1) | (1<<WGM01) | (1<<WGM00); //COM->Non-Inverting Mode and WGM->fast PWM Mode
	TCCR0B = (1<<CS01); //CS->Clock Prescaler(clk/8)
	
	TCCR3A = (1<<COM3A1) | (1<<WGM30);
	TCCR3B = (1<<CS31) | (1<<WGM32);
}

void LED_brightness(uint8_t brightness, uint8_t led){
	if (brightness == 0){
		if(led == 0){
			TCCR0A &= ~(1<<COM0B1);
			PORTG &= ~(1<<PG5);
		}
		else if(led == 1){
			TCCR3A &= ~(1<<COM3A1);
			PORTE &= ~(1<<PE3);
		}
	}
	else{
		if(led == 0){
			TCCR0A |= (1<<COM0B1);
			OCR0B = brightness;
		}
		else if (led == 1){
			TCCR3A |= (1<<COM3A1);
			OCR3A = brightness;
		}
	}
}