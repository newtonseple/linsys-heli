/*
 * IncFile1.h
 *
 * Created: 30.08.2016 15:11:31
 *  Author: didrikr
 */ 
#include "hardware_constants.h"

#ifndef UART_H
#define UART_H

#define BAUD 9600
#define BAUDRATE (((F_CPU)/(BAUD*16UL))-1)

void uart_init();
unsigned char uart_getc();
void uart_putc(unsigned char data);



#endif /*UART_H*/