/*
 * CFile1.c
 *
 * Created: 30.08.2016 15:11:21
 *  Author: didrikr
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/iom162.h>
#include "uart.h"
#include "led.h"
#include <avr/delay.h>


#include <stdio.h>

void uart_putc( unsigned char data ){
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

unsigned char uart_getc(){
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}


void uart_init(){
	/* Set baud rate */
	UBRR0H = (BAUDRATE >> 8);
	UBRR0L = BAUDRATE;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data*/
	UCSR0C = (1<<URSEL0)|(3<<UCSZ00);
	
	/*Enable interrupt for RXC*/
	UCSR0B |= (1 << RXCIE0);
	
	fdevopen(uart_putc,uart_getc);
}

ISR(USART0_RXC_vect){
	unsigned char c = UDR0;
	uart_putc(c);	
}
