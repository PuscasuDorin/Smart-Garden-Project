#include <avr/io.h>
#include "LightSensor.h"
#include "ADC.h"
#include <math.h>

static uint8_t ADC_channel = 0;
static uint32_t R_val = 9800; //ohm
static float V_ref_val = 5.0f; //V

void LightSensor_init(uint8_t ADC_channel_param, uint32_t R_val_param, float V_ref_val_param){
	ADC_channel = ADC_channel_param;
	R_val = R_val_param;
	V_ref_val = V_ref_val_param;
	
	ADC_init();
}

float read_LightSensor(void){
	float adc_val = ADC_read_voltage(ADC_channel, V_ref_val);
	
	if (adc_val < 0.001f){
		 return 0.0f;
	}
	else{
		float R_light_sensor = (R_val*(V_ref_val-adc_val))/adc_val;
		return R_light_sensor;
	}
}

float read_LightSensor_LUX(void){
	
	float R_light_sensor = read_LightSensor();

	if (R_light_sensor < 0.001f) {
		return 0.0f;
	}
	else
	{
	  float lux = powf(12000000.0f / read_LightSensor(), 0.965f);  
	  return lux;
	}
}