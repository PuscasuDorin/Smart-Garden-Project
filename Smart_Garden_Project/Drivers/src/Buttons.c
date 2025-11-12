#include <avr/io.h>
#include "Buttons.h"
#include "config.h"
#include <avr/interrupt.h>
#include <stdbool.h>
#include "TIM.h"

volatile bool up_button_pressed = 0;
volatile bool down_button_pressed = 0;
volatile bool select_button_pressed = 0;
static uint32_t up_button_last_press = 0;
static uint32_t down_button_last_press = 0;

void buttons_init(void){
	DDRB &= ~((1 << up_b_pin) | (1 << down_b_pin) | (1 << select_b_pin));

	PORTB |= (1 << up_b_pin) | (1 << down_b_pin) | (1 << select_b_pin);
	
	PCMSK0 = (1<<up_b_pin)|(1<<down_b_pin)|(1<<select_b_pin);
	PCICR |= (1<<PCIE0);
}

ISR(PCINT0_vect){
	uint32_t now_time = system_time_ms();
	
	if (!(PINB & (1 << up_b_pin)) && (now_time - up_button_last_press > BUTTONS_DEBOUNCE_MS)) {
		up_button_pressed = 1;
		up_button_last_press = now_time;
	}
	
	if (!(PINB & (1 << down_b_pin)) && (now_time - down_button_last_press > BUTTONS_DEBOUNCE_MS)) {
		down_button_pressed = 1;
		down_button_last_press = now_time;
	}

	select_button_pressed = !(PINB & (1 << select_b_pin));
}