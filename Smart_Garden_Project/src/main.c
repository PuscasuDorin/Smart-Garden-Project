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
#include "ADC.h"
#include "UART.h"
#include "LightSensor.h"
#include "LM35.h"
#include <stdio.h>

#define led_port &PORTE
#define led_pin	PE4

int main(void)
{
	//ADC_init();
	//PWM_init();
	LM35_init(15,5);
	//LightSensor_init(1,9800,5.0f);
	UART_Init(9600);
	UART_TransmitString("Starting...");
	PWM_init(led_port, led_pin);
    while (1) 
    {
		/*
		set_LED_Brightness(led_port, led_pin,0);
		_delay_ms(500);
		set_LED_Brightness(led_port, led_pin,30);
		_delay_ms(500);
		set_LED_Brightness(led_port, led_pin,50);
		_delay_ms(500);
		set_LED_Brightness(led_port, led_pin,70);
		_delay_ms(500);
		set_LED_Brightness(led_port, led_pin,100);
		_delay_ms(500);
		set_LED_Brightness(led_port, led_pin,150);
		_delay_ms(500);
		*/
		float number = read_LM35_Temp();
		char str[6];
		sprintf(str, "%.2f", number);
		UART_TransmitString(str);
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		_delay_ms(1000);
		
		
    }
}