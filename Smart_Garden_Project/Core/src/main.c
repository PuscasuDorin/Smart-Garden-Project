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
	bool watering = false;
	uint16_t watering_time = 4000;
	uint16_t now_watering_time = 0;
	uint16_t dry_soil_threshold;
	uint16_t high_temp_threshold = 26;
	uint16_t strong_light_threshold;
	uint16_t darkness_threshold;
	uint8_t overflow_read = 0;
	bool overflow = false;
	float overflow_threshold = 0.5f;
	//char buffer[16];
	
	drivers_and_peripherals_init();
	
    while (1) 
    {
		uint32_t global_time = system_time_ms();
		if(global_time % 503 == 0){
			//0.5s
			overflow_read = ADC_read_voltage(overflow_sensor_adc_channel, overflow_sensor_V_ref);
			if(overflow_read >= overflow_threshold){
				overflow = true;
				watering = false;
			}
			else if(overflow_read < overflow_threshold && overflow){
				overflow = false;
			}
			
			UI_set_temperature(temperature_celsius);
			UI_set_light_procent(light_procent);
			UI_set_soil_moisture(soil_moisture);
			UI_set_water_level(water_level);
			set_overflow_value(overflow);
			
			LCD_UI_UpdateData();
			
			if(watering && system_time_ms()- now_watering_time >= watering_time){
				watering = false;
			}
			
			start_pump(watering);
		}
		
		if(global_time % 10007 == 0){
			//30s for Temperature Sensor 29993
			temperature_celsius = read_LM35_Temp();
		}
		
		if(global_time % 11971  == 0){
			//1min for Light Sensor 59993
			light_procent = read_LightSensor_Percentages();
			
		}
		
		if(global_time % 13999  == 0){
			//1h for Soil Moisture Sensor 3599993UL
			soil_moisture = ADC_read_voltage(soil_sensor_adc_channel, soil_sensor_V_ref);
			if (soil_moisture <= dry_soil_threshold && !overflow){
				if(temperature_celsius >= high_temp_threshold){
					if(light_procent <= darkness_threshold){
						now_watering_time = system_time_ms();
						watering = true;
					}
				}
				else{
					now_watering_time = system_time_ms();
					watering = true;
				}
			}
		}
		
		if(global_time % 15997  == 0){
			//2h for Water Level Sensor 7199993UL
			water_level = ADC_read_voltage(water_sensor_adc_channel, water_sensor_V_ref);
		}
    }
}