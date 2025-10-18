/*
 * Smart_Garden_Project.c
 *
 * Created: 10/17/2025 3:11:53 PM
 * Author : Dorin
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "PWM.h"

int main(void)
{
    DDRG = (1<<PG5); //led 0
	DDRE = (1<<PE3); //led 1
	PWM_init();
	uint8_t value0 = 0x00;
	uint8_t value1 = 0x80;
	uint8_t dir = 1;
    while (1) 
    {
		LED_brightness(value0,0);
		LED_brightness(value1,1);

		if(value0 == 0x01){
			dir = 1;
			value1 = 0x80;
		}
		else if(value0 == 0x80){
			dir = 0;
			value1 = 0x00;
		}
		if(value0 == 0x00){
			value0++;
	    }
		if(value1 == 0x00){
			value1++;
		}
		
		if(dir){
			value0 = value0 << 1;
			LED_brightness(value0,0);
			
			value1 = value1 >> 1;
			LED_brightness(value1,1);
		}
		else if(!dir){
			value0 = value0 >> 1;
			LED_brightness(value0, 0);
			
			value1 = value1 << 1;
			LED_brightness(value1,1);
		}
		_delay_ms(200);
    }
}