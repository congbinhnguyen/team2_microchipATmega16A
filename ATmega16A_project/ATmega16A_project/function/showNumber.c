/*
 * showNumber.c
 *
 * Created: 9/28/2024 11:43:08 PM
 *  Author: binhc
 */

#include "..\header1.h"

void showDot(uint8_t dot);

void showNumber(uint8_t number, uint8_t orderLED, uint8_t dot)
{
	// bit dot (first)
	showDot(dot);

	// counter loop (second)
	uint8_t c;
	for (c = 0; c < 7; c++)
	{
		if (~number & 0b1)
		{
			// SH_CP LOW
			PORTB = 0b00000110;
			// SH_CP HIGH
			PORTB = 0b00000111;
		}
		else
		{
			// DIO LOW
			PORTB = 0b00000101;
			// SH_CP LOW
			PORTB = 0b000100;
			// SH_CP HIGH
			PORTB = 0b00000101;
			// DIO HIGH
			PORTB = 0b00000111;
		}
		number = number >> 1;
	}

	// loop orderLED (third)
	for (c = 0; c <= 7; c++)
	{
		if (1 == (orderLED & 0b1))
		{
			// SH_CP LOW
			PORTB = 0b00000110;
			// SH_CP HIGH
			PORTB = 0b00000111;
		}
		else
		{
			// DIO LOW
			PORTB = 0b00000101;
			// SH_CP LOW
			PORTB = 0b000100;
			// SH_CP HIGH
			PORTB = 0b00000101;
			// DIO HIGH
			PORTB = 0b00000111;
		}
		orderLED = orderLED >> 1;
	}

	//	export data - ST_CP
	PORTB = 0b00000011;
	PORTB = 0b00000111;
}

void showDot(uint8_t dot)
{
	if (dot == 1)
	{
		// DIO LOW
		PORTB = 0b00000101;
		// SH_CP LOW
		PORTB = 0b000100;
		// SH_CP HIGH
		PORTB = 0b00000101;
		// DIO HIGH
		PORTB = 0b00000111;
	}
	else
	{
		// SH_CP LOW
		PORTB = 0b00000110;
		// SH_CP HIGH
		PORTB = 0b00000111;
	}
}
