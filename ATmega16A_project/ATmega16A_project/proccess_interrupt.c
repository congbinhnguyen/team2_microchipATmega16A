/*
 * proccess_interrupt.c
 *
 * Created: 11/9/2024 11:58:49 PM
 *  Author: binhc
 */ 

#include "proccess_interrupt.h"

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