
#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

	void LightSensor_init(uint8_t ADC_channel_param, uint32_t R_ref_param, float V_ref_param);

	float read_LightSensor(void);

	float read_LightSensor_LUX(void);
	
	float read_LightSensor_Percentages(void);

#endif /* LIGHTSENSOR_H_ */