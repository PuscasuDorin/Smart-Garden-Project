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
	Drivers_init();
	Peripherals_init();
	
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
		LCD_gotoxy(0,0);
		LCD_print("Temp:");
		LCD_print(str);	
		
		float num =  ADC_read_voltage(1,5);
		char strr[6];
		sprintf(strr, "%.2f", num);
		UART_TransmitString("Water:");
		UART_TransmitString(strr);
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		LCD_gotoxy(0,1);
		LCD_print("Water:");
		LCD_print(strr);
		_delay_ms(1000);
		LCD_clear();
		
		//_delay_ms(1000);
		
		
		
		
    }
}