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


int main(void)
{
	//ADC_init();
	//PWM_init();
	LM35_init(1,5);
	//LightSensor_init(1,9800,5.0f);
	UART_Init(9600);
	UART_TransmitString("Starting...");
    while (1) 
    {
		float number = read_LM35_Temp();
		char str[6];
		sprintf(str, "%.2f", number);
		UART_TransmitString(str);
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		_delay_ms(1000);
    }
}