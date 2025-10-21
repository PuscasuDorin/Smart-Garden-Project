#include <avr/io.h>
#include "LM35.h"
#include "ADC.h"
	
	static uint8_t LM35_channel = 0;
	static float V_ref = 5.0f; //V
	
	void LM35_init(uint8_t channel, float V_ref_param){
		LM35_channel = channel;
		V_ref = V_ref_param;
		
		ADC_init();
	}
	
	float read_LM35_Temp(void){
		float temperature = ADC_read_voltage(LM35_channel,V_ref) * 100.0f;
		
		return temperature;
	}
	