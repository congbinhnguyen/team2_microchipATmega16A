/*
 * ATmega16A_project.c
 *
 * Created: 9/28/2024 11:42:09 PM
 * Author : binhc
 */ 

#include "header1.h"
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

// declare variable data
uint32_t data = 3000000000; // inout data


int main(void)
{
	// setting DDRB register
	DDRB = 0b00000111;
	
	while (1) 
    {
		// display data
		processNumber (data);
    }
	
	return 0;
}

