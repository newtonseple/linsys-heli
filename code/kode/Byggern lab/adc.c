/*
 * adc.c
 *
 * Created: 09.09.2016 17:33:07
 *  Author: berntjd
 */ 
#include <util/delay.h>
#include "hardware_constants.h"
#include "adc.h"

#define ADC_ADDRESS 0x1400
#define CONVERSION_WAIT_TIME 80 // microseconds. At least 40 microseconds. 
#define STEADY_OUTPUT_WAIT_TIME 80 // microseconds. At least 400ns? Experimentally figured at least 65micro seconds 

uint8_t adc_get_val(const uint8_t channel){
	_delay_us(STEADY_OUTPUT_WAIT_TIME);
	volatile uint8_t* adc = ADC_ADDRESS;
	*adc = channel;
	_delay_us(CONVERSION_WAIT_TIME);
	return *adc;
}

void adc_test(){
	while(1){
		printf("ADC CH1: %d \t CH2: %d\n", adc_get_val(ADC_CH1), adc_get_val(ADC_CH2));
		_delay_ms(100);
	}
}