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
#include <avr/interrupt.h>

int main(void)
{
	float temperature_celsius = 0.0f;
	float light_procent = 0.0f;
	float soil_moisture = 0.0f;
	float water_level = 0.0f;
	uint8_t water_level_cycles = 0;
	
	Peripherals_init();
	Drivers_init();
	
    while (1) 
    {
		uint32_t global_time = TIM_value();
		
		if(global_time % 503 == 0){
			//0.5s for LCD refresh
		}
		
		if(global_time % 29993 == 0){
			//30s for Temperature Sensor
			temperature_celsius = read_LM35_Temp();
		}
		
		if(global_time % 59993  == 0){
			//1min for Light Sensor
			light_procent = read_LightSensor_Percentages();
			
		}
		
		if(global_time % 3599993UL  == 0){
			//1h for Soil Moisture Sensor
		}
		
		if(global_time % 7199993UL  == 0){
			//2h for Water Level Sensor
		}
		
		
		
		/*	
		char strr[10];
		sprintf(strr, "%lu", global_time);
		UART_TransmitString(strr);
		UART_TransmitString("\n\r");
		
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
	
	
		float num =  read_LightSensor_Percentages();
		char strr[6];
		sprintf(strr, "%.2f", num);
		UART_TransmitString("Light:");
		UART_TransmitString(strr);
		UART_TransmitByte('\n');
		UART_TransmitByte('\r');
		//LCD_gotoxy(0,1);
		//LCD_print("Light:");
		//LCD_print(strr);
		_delay_ms(1000);
		//LCD_clear();
		
		//_delay_ms(1000);
		
		*/
		
    }
}