#include <avr/io.h>
#include "PWM.h"
#include <stdbool.h>
#include "UART.h"

static void set_PWM_Pin(volatile uint8_t *pwm_port,uint8_t pwm_pin, uint8_t pwm_value, bool init);

void PWM_init (volatile uint8_t *pwm_port,uint8_t pwm_pin){
	set_PWM_Pin(pwm_port, pwm_pin, 0, 1);
}

void set_PumpSpeed(volatile uint8_t *pwm_port, uint8_t set_pumpPin, uint8_t speed){
	set_PWM_Pin(pwm_port, set_pumpPin, speed, 0);
}

void set_LED_Brightness(volatile uint8_t *pwm_port, uint8_t set_ledPin, uint8_t brightness){
	set_PWM_Pin(pwm_port, set_ledPin, brightness, 0);
}

static void set_PWM_Pin(volatile uint8_t *pwm_port,uint8_t pwm_pin, uint8_t pwm_value, bool init){
	uint8_t index =20;
	if(pwm_port == &PORTE){
		switch(pwm_pin){
			case PE3:
				index = 3;
				break;
			case PE4:
				index = 0;
				break;
			case PE5:
				index = 1;
				break;
		}
	}
	if(pwm_port == &PORTG){
		if(pwm_pin == PG5){
			index = 2;
		}
	}
	if(pwm_port == &PORTH){
		switch(pwm_pin){
			case PH3:
				index = 4;
				break;
			case PH4:
				index = 5;
				break;
			case PH5:
				index = 6;
				break;
			case PH6:
				index = 7;
				break;
		}
	}
	if(pwm_port == &PORTB){
		switch(pwm_pin){
			case PB4:
				index = 8;
				break;
			case PB5:
				index = 9;
				break;
			case PB6:
				index = 10;
				break;
			case PB7:
				index = 11;
				break;
		}
	}
	
	switch(index){
		case 0:
			if(init){
				TCCR3A = (1<<COM3B1) | (1<<WGM30);
				TCCR3B = (1<<CS31) | (1<<WGM32);
			
				DDRE = (1<<PE4);
			}		
			if(pwm_value == 0){
				TCCR3A &= ~(1<<COM3B1);
				PORTE &= ~(1<<PE4);
			}
			else{
				TCCR3A |= (1<<COM3B1);
				OCR3B = pwm_value;
			}
			break;
			
		case 1:
			if(init){
				TCCR3A = (1<<COM3C1) | (1<<WGM30);
				TCCR3B = (1<<CS31) | (1<<WGM32);
				
				DDRE = (1<<PE5);
			}
			if(pwm_value == 0){
				TCCR3A &= ~(1<<COM3C1);
				PORTE &= ~(1<<PE5);
			}
			else{
				TCCR3A |= (1<<COM3C1);
				OCR3C = pwm_value;
			}
			break;
			
		case 2:
			UART_Init(9600);
			UART_TransmitString("Error: PG5 is a timer-dedicated pin!\n\r");
			while(1);
		/*
			if(init){
				TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
				TCCR0B = (1<<CS01);
				
				DDRG = (1<<PG5);
			}
			if(pwm_value == 0){
				TCCR0A &= ~(1<<COM0B1);
				PORTG &= ~(1<<PG5);
			}
			else{
				TCCR0A |= (1<<COM0B1);
				OCR0B = pwm_value;
			}
		*/
			break;
			
		case 3:
			if(init){
				TCCR3A = (1<<COM3A1) | (1<<WGM30);
				TCCR3B = (1<<CS31) | (1<<WGM32);
				
				DDRE = (1<<PE3);
			}
			if(pwm_value == 0){
				TCCR3A &= ~(1<<COM3A1);
				PORTE &= ~(1<<PE3);
			}
			else{
				TCCR3A |= (1<<COM3A1);
				OCR3A = pwm_value;
			}
			break;
			
		case 4:
			if(init){
				TCCR4A = (1<<COM4A1) | (1<<WGM40);
				TCCR4B = (1<<CS41) | (1<<WGM42);
				
				DDRH = (1<<PH3);
			}
			if(pwm_value == 0){
				TCCR4A &= ~(1<<COM4A1);
				PORTH &= ~(1<<PH3);
			}
			else{
				TCCR4A |= (1<<COM4A1);
				OCR4A = pwm_value;
			}
			break;
			
		case 5:
			if(init){
				TCCR4A = (1<<COM4B1) | (1<<WGM40);
				TCCR4B = (1<<CS41) | (1<<WGM42);
				
				DDRH = (1<<PH4);
			}
			if(pwm_value == 0){
				TCCR4A &= ~(1<<COM4B1);
				PORTH &= ~(1<<PH4);
			}
			else{
				TCCR4A |= (1<<COM4B1);
				OCR4B = pwm_value;
			}
			break;
			
		case 6:
			if(init){
				TCCR4A = (1<<COM4C1) | (1<<WGM40);
				TCCR4B = (1<<CS41) | (1<<WGM42);
				
				DDRH = (1<<PH5);
			}
			if(pwm_value == 0){
				TCCR4A &= ~(1<<COM4C1);
				PORTH &= ~(1<<PH5);
			}
			else{
				TCCR4A |= (1<<COM4C1);
				OCR4C = pwm_value;
			}
			break;
			
		case 7:
			if(init){
				TCCR2A = (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
				TCCR2B = (1<<CS21);
				
				DDRH = (1<<PH6);
			}
			if(pwm_value == 0){
				TCCR2A &= ~(1<<COM2B1);
				PORTH &= ~(1<<PH6);
			}
			else{
				TCCR2A |= (1<<COM2B1);
				OCR2B = pwm_value;
			}
			break;
			
		case 8:
			if(init){
				TCCR2A = (1<<COM2A1) | (1<<WGM21) | (1<<WGM20);
				TCCR2B = (1<<CS21);
				
				DDRB = (1<<PB4);
			}
			if(pwm_value == 0){
				TCCR2A &= ~(1<<COM2A1);
				PORTB &= ~(1<<PB4);
			}
			else{
				TCCR2A |= (1<<COM2A1);
				OCR2A = pwm_value;
			}
			break;
			
		case 9:
			if(init){
				TCCR1A = (1<<COM1A1) | (1<<WGM10);
				TCCR1B = (1<<CS11) | (1<<WGM12);
				
				DDRB = (1<<PB5);
			}
			if(pwm_value == 0){
				TCCR1A &= ~(1<<COM1A1);
				PORTB &= ~(1<<PB5);
			}
			else{
				TCCR1A |= (1<<COM1A1);
				OCR1A = pwm_value;
			}
			break;
			
		case 10:
			if(init){
				TCCR1A = (1<<COM1B1) | (1<<WGM10);
				TCCR1B = (1<<CS11) | (1<<WGM12);
				
				DDRB = (1<<PB6);
			}
			if(pwm_value == 0){
				TCCR1A &= ~(1<<COM1B1);
				PORTB &= ~(1<<PB6);
			}
			else{
				TCCR1A |= (1<<COM1B1);
				OCR1B = pwm_value;
			}
			break;
			
		case 11:
			UART_Init(9600);
			UART_TransmitString("Error: PB7 is a timer-dedicated pin!\n\r");
			while(1);
		/*
			if(init){
				TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00); //COM->Non-Inverting Mode and WGM->fast PWM Mode
				TCCR0B = (1<<CS01); //CS->Clock Prescaler(clk/8)
				
				DDRB = (1<<PB7);
			}
			if(pwm_value == 0){
				TCCR0A &= ~(1<<COM0A1);
				PORTB &= ~(1<<PB7);
			}
			else{
				TCCR0A |= (1<<COM0A1);
				OCR0A = pwm_value;
			}
		*/
			break;
	}
}