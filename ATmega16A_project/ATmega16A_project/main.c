/*
 * ATmega16A_project.c
 *
 * Created: 9/28/2024 11:42:09 PM
 * Author : binhc
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "header1.h"
#include <util/delay.h>


int main(void)
{
	DDRB = 0b00000111;

	uint32_t data = 12345678;
	
	
	while (1) 
    {
		processNumber (data)  ;
    }
	
	return 0;
}

