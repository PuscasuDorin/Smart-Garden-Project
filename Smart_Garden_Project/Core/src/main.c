/*
 * Smart_Garden_Project.c
 *
 * Created: 10/17/2025 3:11:53 PM
 * Author : Dorin
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "system.h"

int main(void)
{
	//LightSensor_init(1,9800,5.0f);
	UART_TransmitString("Starting...");
	
    while (1) 
    {
		
		
		float number =  read_LM35_Temp();
		char str[6];
		
		sprintf(str, "%.2f", number);
		UART_TransmitString("Temp:");
		UART_TransmitString(str);
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		_delay_ms(1000);
		
		float num =  ADC_read_voltage(4,5);
		char strr[6];
		sprintf(strr, "%.2f", num);
		UART_TransmitString("Water:");
		UART_TransmitString(strr);
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		_delay_ms(1000);
		
		UART_TransmitString("Start pump...");
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		set_PumpSpeed(led_port,led_pin, 100);
		
		//_delay_ms(1000);
		
		
		
		
    }
}