#include <avr/io.h>
#include "TIM.h"
#include <avr/interrupt.h>

volatile uint32_t ms_counter = 0;

void TIM_init(void){
	TCCR0A = (1<<WGM01);			//Set WGM to CTC mode
	TCCR0B = (1<<CS01) | (1<<CS00); //Set Clock Prescaler -> 16MHz / 64 = 250k / 1000ms -> 250 ticks/ms 
	
	OCR0A = 249;
	
	TIMSK0 |= (1<<OCIE0A);
	
	sei();
}

ISR(TIMER0_COMPA_vect){
	ms_counter++;
}

uint32_t TIM_value(void){
	uint32_t time;
	
	cli();

	time = ms_counter;
	
	sei();
	
	return time;
}