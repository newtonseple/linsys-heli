/*
 * joystick.c
 *
 * Created: 09.09.2016 18:56:36
 *  Author: berntjd
 */ 
#include <util/delay.h>
#include "hardware_constants.h"

#include "adc.h"
#include "joystick.h"

uint8_t joystick_get_axis(const uint8_t axis){
	uint8_t channel;
	switch(axis){
		case JOYSTICK_X:
			channel = ADC_CH2;
			break;
		case JOYSTICK_Y:
			channel = ADC_CH1;
			break;
	}
	return adc_get_val(channel);
}

void joystick_test(){
	while(1){
		printf("X: %d \t Y: %d\n", joystick_get_axis(JOYSTICK_X), joystick_get_axis(JOYSTICK_Y));
		//printf("ADC: %d\n", adc_get_val(ADC_CH2));
		_delay_ms(300);
	}
}