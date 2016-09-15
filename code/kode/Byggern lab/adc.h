/*
 * adc.h
 *
 * Created: 09.09.2016 17:31:56
 *  Author: berntjd
 */ 


#ifndef ADC_H_
#define ADC_H_

#define ADC_CH1 0x04 // Uses ADC MUX mode "Single-ended". Number depends on adc datasheet. 
#define ADC_CH2 0x05 

uint8_t adc_get_val(const uint8_t channel); 
void adc_test();

#endif /* ADC_H_ */