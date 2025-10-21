
#ifndef LM35_H_
#define LM35_H_

	void LM35_init(uint8_t channel, float V_ref_param);
	
	float read_LM35_Temp(void);

#endif /* LM35_H_ */