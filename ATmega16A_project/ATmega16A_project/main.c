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

#define CLOCK PB0 // SH-CP | SCLK (Shift Clock)
#define DATA PB1  // DS | DIO
#define LATCH PB2 // ST-CP (Storage Clock) | RCLK (Register Clock)

void setup(void);

int main(void)
{
	setup();

	// declare variable data
	uint32_t data = 34567; // inout data

	while (1)
	{
		// display data
		processNumber(data);
	}

	return 0;
}

void setup(void)
{
	DDRB |= (1 << CLOCK);
	DDRB |= (1 << DATA);
	DDRB |= (1 << LATCH);
}