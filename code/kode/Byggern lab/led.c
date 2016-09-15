/*
 * CFile1.c
 *
 * Created: 30.08.2016 17:04:38
 *  Author: didrikr
 */ 
#include <avr/io.h>
#include <util/delay.h>

void led_init(){
	DDRA |= (1 << PA0);
	PORTA &= 0x00;
}

void led_blink(){
	PORTA |= (1 << PA0);
	_delay_ms(200);
	PORTA &= ~(1 << PA0);
	_delay_ms(200);
}