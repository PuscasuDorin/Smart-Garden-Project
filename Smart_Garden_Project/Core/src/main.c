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
	drivers_and_peripherals_init();
	
	float temperature_celsius = first_read_temperature_celsius;
	float light_procent = first_read_light_procent;
	float soil_moisture = first_read_soil_moisture;
	float water_level = first_read_water_level;
	
	uint8_t water_level_cycles = 0;
	uint8_t new_water_level_cycles = 0;
	bool watering = false;
	uint16_t watering_time = 4001;
	uint32_t now_watering_time = 0;
	uint16_t dry_soil_threshold = 1.5f;
	uint16_t high_temp_threshold = 26;
	uint16_t strong_light_threshold = 90;
	//uint16_t darkness_threshold = 10;
	//uint8_t overflow_read = 0;
	//float overflow_threshold = 0.5f;
	bool overflow = false;
	
    while (1) 
    {
		uint32_t global_time = system_time_ms();
		if(global_time % 503 == 0){
			//0.5s
			/*
			overflow_read = ADC_read_voltage(overflow_sensor_adc_channel, overflow_sensor_V_ref);
			if(overflow_read >= overflow_threshold){
				overflow = true;
				watering = false;
			}
			else if(overflow_read < overflow_threshold && overflow){
				overflow = false;
			}
			*/
			
			if(watering && (system_time_ms()- now_watering_time) >= watering_time){
				watering = false;
				set_LED_Brightness(red_led_port, red_led_pin, 0);
				start_pump(watering);
				
				if(water_level >= 0.3){
					water_level_cycles++;
				}
				else if(new_water_level_cycles > 0){
					new_water_level_cycles--;
				}
			}
			
			if(water_level < 0.3 && new_water_level_cycles == 0){
				new_water_level_cycles = water_level_cycles * 1.5;
				water_level_cycles = 0;
			}
			
			UI_set_temperature(temperature_celsius);
			UI_set_light_procent(light_procent);
			UI_set_soil_moisture(soil_moisture);
			UI_set_water_level(water_level);
			UI_set_water_level_cycles(new_water_level_cycles);
			//set_overflow_value(overflow);
			
			LCD_UI_UpdateData();
		}
		
		if(global_time % 29993 == 0){
			//30s for Temperature Sensor 29993
			read_LM35_Temp();
			read_LM35_Temp();
			temperature_celsius = read_LM35_Temp();
		}
		
		if(global_time % 59993UL == 0){
			//1min for Light Sensor 59993UL
			read_LightSensor_Percentages();
			read_LightSensor_Percentages();
			light_procent = read_LightSensor_Percentages();
		}
		
		if(global_time % 6300007UL == 0){
			//1h 45m for Water Level Sensor 6300007UL
			water_level = read_water_sensor();
		}
		
		if(global_time % 7199993UL == 0){
			//2h for Soil Moisture Sensor 7199993UL
			soil_moisture = read_soil_sensor();
			
			if (soil_moisture >= dry_soil_threshold && !overflow && !no_water){
				if(temperature_celsius >= high_temp_threshold){
					if(light_procent <= strong_light_threshold){
						set_LED_Brightness(red_led_port, red_led_pin, 100);
						now_watering_time = system_time_ms();
						watering = true;
					}
				}
				else{
					set_LED_Brightness(red_led_port, red_led_pin, 100);
					now_watering_time = system_time_ms();
					watering = true;
				}
				start_pump(watering);
			}
		}
    }
}