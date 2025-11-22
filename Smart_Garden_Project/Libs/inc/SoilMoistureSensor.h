
#ifndef SOILMOISTURESENSOR_H_
#define SOILMOISTURESENSOR_H_

	float read_soil_sensor(void);
	void soil_sensor_init(uint8_t channel, float V_ref_param);

#endif /* SOILMOISTURESENSOR_H_ */