
#ifndef ADC_H_
#define ADC_H_

	void ADC_init(void);

	uint16_t ADC_read(uint8_t channel);

	float ADC_read_voltage(uint8_t channel ,uint8_t V_ref);

#endif /* ADC_H_ */