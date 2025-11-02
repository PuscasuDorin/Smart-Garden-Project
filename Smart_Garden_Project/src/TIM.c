#include <avr/io.h>
#include "TIM.h"

void TIM_init(void){
	TCCR0A = (1<<WGM01);
	TCCR0B = (1<<CS01) | (1<<CS00); //CS->Clock Prescaler(clk/64)
}