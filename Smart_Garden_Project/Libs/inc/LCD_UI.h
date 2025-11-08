
#ifndef LCD_UI_H_
#define LCD_UI_H_

	void UI_set_temperature(float temp_val);
	void UI_set_light_procent(float light_val);
	void UI_set_soil_moisture(float soil_val);
	void UI_set_water_level(float water_val);
	
	void LCD_UI_UpdateData(void);
#endif /* LCD_UI_H_ */