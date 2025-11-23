
#ifndef LCD_TEST_H_
#define LCD_TEST_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LCD_ADDR 0x27

void LCD_init(void);
void LCD_sendCommand(uint8_t cmd);
void LCD_sendData(uint8_t data);
void LCD_clear(void);
void LCD_gotoxy(uint8_t x, uint8_t y);
void LCD_print(char *str);

void LCD_backlightOn(void);
void LCD_backlightOff(void);

#endif /* LCD_TEST_H_ */