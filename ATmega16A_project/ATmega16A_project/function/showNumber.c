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

	// counter loop (seconed)
	uint8_t c;
	for (c = 0; c < 7; c++)
	{
		if (~number & 0b1)
		{
			PORTB = 0b00000110;
			_delay_ms(TIMELIMIT);
			PORTB = 0b00000111;
			_delay_ms(TIMELIMIT);
		}
		else
		{
			PORTB = 0b00000101;
			_delay_ms(TIMELIMIT);
			PORTB = 0b000100;
			_delay_ms(TIMELIMIT);
			PORTB = 0b00000101;
			_delay_ms(TIMELIMIT);
			PORTB = 0b00000111;
			_delay_ms(TIMELIMIT);
		}
		number = number >> 1;
	}

	// loop orderLED (third)
	for (c = 0; c <= 7; c++)
	{
		if (1 == (orderLED & 0b1))
		{
			PORTB = 0b00000110;
			_delay_ms(TIMELIMIT);
			PORTB = 0b00000111;
			_delay_ms(TIMELIMIT);
		}
		else
		{
			PORTB = 0b00000101;
			_delay_ms(TIMELIMIT);
			PORTB = 0b000100;
			_delay_ms(TIMELIMIT);
			PORTB = 0b00000101;
			_delay_ms(TIMELIMIT);
			PORTB = 0b00000111;
			_delay_ms(TIMELIMIT);
		}
		orderLED = orderLED >> 1;
	}

	//	export data
	PORTB = 0b00000011;
	_delay_ms(TIMELIMIT);
	PORTB = 0b00000111;
	_delay_ms(TIMELIMIT);
}

void showDot(uint8_t dot)
{
	if (dot == 1)
	{
		PORTB = 0b00000101;
		_delay_ms(TIMELIMIT);
		PORTB = 0b000100;
		_delay_ms(TIMELIMIT);
		PORTB = 0b00000101;
		_delay_ms(TIMELIMIT);
		PORTB = 0b00000111;
		_delay_ms(TIMELIMIT);
	}
	else
	{
		PORTB = 0b00000110;
		_delay_ms(TIMELIMIT);
		PORTB = 0b00000111;
		_delay_ms(TIMELIMIT);
	}
}
