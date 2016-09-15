/*
 * Byggern_lab.c
 *
 * Created: 30.08.2016 15:08:23
 *  Author: didrikr
 */

#include "hardware_constants.h"
#include <avr/interrupt.h>
#include <avr/io.h> 
#include <util/delay.h>
#include "uart.h"
#include "led.h"
#include "sram.h"
#include "adc.h"
#include "joystick.h"

#include <stdio.h>

void gal_test(){
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	volatile char *oled = (char *) 0x1000; // Start address for OLED
	volatile char *adc = (char *) 0x1400; // Start address for ADC
	DDRC |= (1 << PC0);
	PORTC &= 0x00;
	
	while(1) {
		PORTC |= (1 << PC0);
		printf("RAM\n");
		*ext_ram = 0xFF;
		_delay_ms(10);
		PORTC &= (1 << PC0);
		printf("OLED\n");
		*oled = 0xFF;
		_delay_ms(10);
		printf("ADC\n");
		*adc = 0xFF;
		_delay_ms(10);
	}
}

int main(void)
{
	uart_init();
	sram_init();
	
	//adc_test();
	joystick_test();
}

