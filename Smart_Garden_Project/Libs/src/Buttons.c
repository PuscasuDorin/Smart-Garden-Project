#include <avr/io.h>
#include "Buttons.h"
#include "config.h"
#include <avr/interrupt.h>
#include <stdbool.h>

volatile bool button_up_pressed = 0;
volatile bool button_down_pressed = 0;
volatile bool button_start_pressed = 0;

void buttons_init(void){
	DDRB &= ~((1 << up_b_pin) | (1 << down_b_pin) | (1 << start_b_pin));

	PORTB |= (1 << up_b_pin) | (1 << down_b_pin) | (1 << start_b_pin);
	
	PCMSK0 = (1<<up_b_pin)|(1<<down_b_pin)|(1<<start_b_pin);
	PCICR |= (1<<PCIE0);
}

ISR(PCINT0_vect){
	if (!(PINB & (1 << up_b_pin))) button_up_pressed = 1;
	if (!(PINB & (1 << down_b_pin))) button_down_pressed = 1;

	button_start_pressed = !(PINB & (1 << start_b_pin));
}