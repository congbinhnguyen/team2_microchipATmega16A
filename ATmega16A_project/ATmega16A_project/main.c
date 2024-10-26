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
volatile uint8_t object_in_detected = 0;
volatile uint8_t object_out_detected = 0;

volatile uint8_t buzzed_in = 0;
volatile uint8_t buzzed_count_in = 0;

volatile uint8_t buzzed_out = 0;
volatile uint8_t buzzed_count_out = 0;

ISR(INT0_vect)
{
	if (!object_in_detected)
	{
		object_counter++;
		object_in_detected = 1;
		
		if (!buzzed_in)
		{
			buzzed_in = 1;
			disable_overflow_interrupt();
			enable_overflow_interrupt();
		}
	}
}

ISR(INT1_vect)
{
	if (object_counter > 0)
	{
		if (!object_out_detected)
		{
			object_counter--;
			object_out_detected = 1;
			
			if (!buzzed_out)
			{
				buzzed_out = 1;
				disable_overflow_interrupt();
				enable_overflow_interrupt();
			}
		}
	}

}

ISR(TIMER1_OVF_vect)
{
    // Increment counters for in and out buzzed events
    if (buzzed_in) 
	{
        buzzed_count_in++;
        PORTD |= (1 << BUZZER);

        if (buzzed_count_in >= 2) 
		{
			PORTD &= ~(1 << BUZZER);
			disable_overflow_interrupt();
        }
    }

    if (buzzed_out) 
	{
        buzzed_count_out++;
        PORTD |= (1 << BUZZER);

        if (buzzed_count_out >= 2) 
		{
			PORTD &= ~(1 << BUZZER);
            disable_overflow_interrupt();
        }
    }
}

int main(void)
{
	setup();
	// demo();

	while (1)
	{
		// Check if the object is still present
		if (PIND & (1 << PROX_IN))  // If sensor no longer detects the object (high signal)
		{
			object_in_detected = 0;
			buzzed_in = 0;
			buzzed_count_in = 0;
		}

		if (PIND & (1 << PROX_OUT))  // If sensor no longer detects the object (high signal)
		{
			object_out_detected = 0;
			buzzed_out = 0;
			buzzed_count_out = 0;
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
	DDRD &= ~(1 << PROX_IN);
	DDRD &= ~(1 << PROX_OUT);
	DDRD |= (1 << BUZZER);

	// Enable INT0 interrupt 
	GICR |= (1 << INT0);
	// Falling edge trigger of INT0
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);

	// Enable INT1 interrupt 
	GICR |= (1 << INT1);
	// Falling edge trigger of INT0
	MCUCR |= (1 << ISC11);
	MCUCR &= ~(1 << ISC10);
	
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