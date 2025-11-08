#include <avr/io.h>
#include "TIM.h"
#include <avr/interrupt.h>
#include <stdbool.h>

volatile uint32_t millis_counter = 0;
volatile uint32_t millis_another_counter = 0;
volatile bool start_another_counter = false;


void TIM_init(void){
	TCCR0A = (1<<WGM01);			//Set WGM to CTC mode
	TCCR0B = (1<<CS01) | (1<<CS00); //Set Clock Prescaler -> 16MHz / 64 = 250k / 1000ms -> 250 ticks/ms 
	
	OCR0A = 249;
	
	TIMSK0 |= (1<<OCIE0A);
	
	sei();
}

ISR(TIMER0_COMPA_vect){
	millis_counter++;
	
	if(start_another_counter){
		millis_another_counter++;
	}
}

uint32_t system_time_ms(void){
	uint32_t time;
	
	cli();

	time = millis_counter;
	
	sei();
	
	return time;
}

uint32_t ms_counter(void){
	uint32_t time;
	
	if(!start_another_counter){
		start_another_counter = true;
	}
	
	cli();

	time = millis_another_counter;
	
	sei();
	
	return time;
}

void stop_ms_counter(void){
	start_another_counter = false;
}