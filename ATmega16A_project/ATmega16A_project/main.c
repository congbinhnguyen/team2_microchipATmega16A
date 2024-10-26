/*
 * ATmega16A_project.c
 *
 * Created: 9/28/2024 11:42:09 PM
 * Author : binhc + thai
 */

#include "header1.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

void setup(void);
void demo(void);
void enable_overflow_interrupt(void);
void disable_overflow_interrupt(void);

volatile uint32_t object_counter = 0;
volatile uint8_t object_detected = 0;

volatile uint8_t buzzed = 0;
volatile uint8_t buzzed_count = 0;

ISR(INT0_vect)
{
	if (!object_detected)
	{
		object_counter++;
		object_detected = 1;
		if (!buzzed)
		{
			buzzed = 1;
			enable_overflow_interrupt();
		}
	}
}

ISR(TIMER1_OVF_vect)
{
	buzzed_count++;
	PORTD ^= (1 << BUZZER);
	if (buzzed_count >= 2)
	{
		disable_overflow_interrupt();
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
			buzzed = 0;
			buzzed_count = 0;
		}

		processNumber(object_counter);
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
	DDRD |= (1 << BUZZER);

	// Enable INT0 interrupt 
	GICR |= (1 << INT0);
	// Falling edge trigger of INT0
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);
	
	// Timer 1 overflow interrupt
	TCCR1A = 0x00;
	TCCR1B = (1 << CS11); // Pre-scaler of 8 -> 0.524s per overflow

	// Enable global interrupt
	sei();
}

void enable_overflow_interrupt(void)
{
	// Initialize Timer1 register
	TCNT1 = 0;
	// Enable Timer1 overflow interrupt
	TIMSK |= (1 << TOIE1);
}

void disable_overflow_interrupt(void)
{
	// Enable Timer1 overflow interrupt
	TIMSK &= ~(1 << TOIE1);
}

void demo(void)
{
	for (uint32_t i = 0; i <= 2000000; i+=3000)
	{
		processNumber(i);
	}
}