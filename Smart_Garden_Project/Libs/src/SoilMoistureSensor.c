#define F_CPU 16000000UL

#include <avr/io.h>
#include "SoilMoistureSensor.h"
#include "ADC.h"
#include <util/delay.h>
#include "config.h"

static uint8_t soil_sensor_channel = 0;
static float V_ref = 5.0f;

void soil_sensor_init(uint8_t channel, float V_ref_param){
	soil_sensor_channel = channel;
	V_ref = V_ref_param;
	
	ADC_init();
}

float read_soil_sensor(void){
	soil_sensor_port |= (1 << soil_sensor_pin);
	_delay_ms(10);
	float soil_moisture = ADC_read_voltage(soil_sensor_channel, V_ref);
	soil_sensor_port &= ~(1 << soil_sensor_pin);
	
	return soil_moisture;
}