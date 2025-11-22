#ifndef WATERLEVELSENSOR_H_
#define WATERLEVELSENSOR_H_

	float read_water_sensor(void);
	void water_sensor_init(uint8_t channel, float V_ref_param);
	
#endif /* WATERLEVELSENSOR_H_ */