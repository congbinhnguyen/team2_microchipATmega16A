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
#include <avr/interrupt.h>

void setup(void);
void demo(void);

uint32_t counter = 0;
volatile uint8_t object_detected = 0;

ISR(INT0_vect)
{
	if (!object_detected)
	{
		counter++;
		object_detected = 1;	
	}
}

int main(void)
{
	setup();
	demo();

	while (1)
	{
		// Check if the object is still present
		if (PIND & (1 << PROX))  // If sensor no longer detects the object (high signal)
		{
			object_detected = 0;
		}

		processNumber(counter);
	}

	return 0;
}

void setup(void)
{
	// Input and Output
	DDRB |= (1 << CLOCK);
	DDRB |= (1 << DATA);
	DDRB |= (1 << LATCH);
	DDRD &= ~(1 << PROX);

	// Enable INT0 interrupt 
	GICR |= (1 << INT0);
	// Falling edge trigger of INT0
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);

	// Enable global interrupt
	sei();
}

void demo(void)
{
	for (uint32_t i = 0; i <= 2000000; i+=500)
	{
		processNumber(i);
	}
}