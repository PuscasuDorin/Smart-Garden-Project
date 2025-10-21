/*
 * Smart_Garden_Project.c
 *
 * Created: 10/17/2025 3:11:53 PM
 * Author : Dorin
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "PWM.h"
#include "ADC.h"
#include "UART.h"
#include "LightSensor.h"
#include <stdio.h>


int main(void)
{
	ADC_init();
	PWM_init();
	LightSensor_init(1,9800,3.3f);
	UART_Init(9600);
    while (1) 
    {

    }
}