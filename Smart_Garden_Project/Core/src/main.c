#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "system.h"
#include "config.h"
#include <avr/interrupt.h>
#include "LCD_UI.h"
#include "Buttons.h"

int main(void)
{
	float temperature_celsius = 0.0f;
	float light_procent = 0.0f;
	float soil_moisture = 0.0f;
	float water_level = 0.0f;
	uint8_t water_level_cycles = 0;
	//char buffer[16];
	
	drivers_and_peripherals_init();
	buttons_init();
	
    while (1) 
    {
		uint32_t global_time = system_time_ms();
		if(global_time % 503 == 0){
			//0.5s for LCD refresh
			UI_set_temperature(temperature_celsius);
			UI_set_light_procent(light_procent);
			UI_set_soil_moisture(soil_moisture);
			UI_set_water_level(water_level);
			
			LCD_UI_UpdateData();
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
    }
}