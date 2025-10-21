
#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

void LightSensor_init(uint8_t ADC_channel_param, uint32_t R_val_param, float V_ref_val_param);
float read_LightSensor(void);
float read_LightSensor_LUX(void);

#endif /* LIGHTSENSOR_H_ */