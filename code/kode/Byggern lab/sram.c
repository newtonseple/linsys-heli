/*
 * ramTest.c
 *
 * Created: 05.09.2016 19:55:54
 *  Author: didrikr
 */ 


#include "hardware_constants.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "led.h"
#include "sram.h"

void sram_init() {
		SFIOR  |= (1 << XMM2);  // Release PC7..4 for JTAG usage
		//SFIOR  |= (1 << XMBK); // enables busskeeper
		MCUCR  |= (1 << SRE);   // Enable external memory
		EMCUCR |= (1 << SRW11); // Max wait
		MCUCR  |= (1 << SRW10); // Max wait
}

void sram_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; ++i) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4p] = %02X (should be %02X)\n", ext_ram + i,retreived_value, some_value);
			write_errors++;
		}
	}
	
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; ++i) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4p] = %02X (should be %02X)\n",(void*)ext_ram + i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with\n%4d errors in write phase and\n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}


void sram_test_lite() {
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	uint8_t some_value = 0x55;
	while(1){
		uint8_t i = 0;
		ext_ram[i] = some_value;
		_delay_ms(10);
		uint8_t retreived_value = ext_ram[i];
		_delay_ms(10);
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4p] = %02X (should be %02X)\n", ext_ram + i,retreived_value, some_value);
			retrieval_errors++;
		}
		else {
			printf("SUCCESS! ext_ram[%4p] = %02X (should be %02X)\n",(void*)ext_ram + i, retreived_value, some_value);
		}
	}
}