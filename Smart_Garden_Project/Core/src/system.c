#include <avr/io.h>
#include "system.h"
#include "config.h"

void Drivers_init(void){
	ADC_init();
	PWM_init(pump_port, pump_pin);
	PWM_init(rgb_r_port, rgb_r_pin);
	PWM_init(rgb_g_port, rgb_g_pin);
	PWM_init(rgb_b_port, rgb_b_pin);
	TIM_init();
}

void Peripherals_init(void){
	LightSensor_init(light_sensor_adc_channel,light_sensor_R_ref,light_sensor_V_ref);
	LM35_init(temp_sensor_adc_channel,temp_sensor_V_ref);
	I2C_Init();
	LCD_init();
	console_init();
}