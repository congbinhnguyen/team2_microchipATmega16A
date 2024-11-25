/*
 * proccessingNumber.c
 *
 * Created: 11/9/2024 11:00:20 PM
 *  Author: binhc
 */ 

#include "LEDdisplay.h"


// ERROR 1: OUT LIMIT NUMBER
void displayError()
{
	showNumber(_E_, LED6, 0);
	showNumber(_R_, LED5, 0);
	showNumber(_R_, LED4, 0);
	showNumber(_O_, LED3, 0);
	showNumber(_R_, LED2, 0);
}

// Convert number to binary
void number2bin(uint8_t *number, uint8_t *orderLED)
{
	// converting number
	switch (*number)
	{
		case 0:
		*number = _ZERO_;
		break;
		
		case 1:
		*number = _ONE_;
		break;
		
		case 2:
		*number = _TWO_;
		break;
		
		case 3:
		*number = _THREE_;
		break;
		
		case 4:
		*number = _FOUR_;
		break;
		
		case 5:
		*number = _FIVE_;
		break;
		
		case 6:
		*number = _SIX_;
		break;
		
		case 7:
		*number = _SEVEN_;
		break;
		
		case 8:
		*number = _EIGHT_;
		break;
		
		case 9:
		*number = _NINE_;
		break;
	}
	

	// converting orderLED
	switch (*orderLED)
	{
		case 1:
		*orderLED = LED1;
		break;
		case 2:
		*orderLED = LED2;
		break;
		case 3:
		*orderLED = LED3;
		break;
		case 4:
		*orderLED = LED4;
		break;
		case 5:
		*orderLED = LED5;
		break;
		case 6:
		*orderLED = LED6;
		break;
		case 7:
		*orderLED = LED7;
		break;
		case 8:
		*orderLED = LED8;
		break;
	}
}

// device number to small
void processNumber(uint32_t data)
{
	if (data < MIN_VALUE || data > MAX_VALUE)
	{
		displayError();
	}
	else
	{
		for (uint8_t counter = 1; counter <= NUM_DIGITS; counter++)
		{
			uint8_t number = data % 10;
			data /= 10;
			uint8_t orderLED = counter;
			number2bin(&number, &orderLED);

			uint8_t dot = 0;
			if (counter == 4)
			{
				dot = 1;
			}
			else
			{
				dot = 0;
			}

			showNumber(number, orderLED, dot);

			dot = 0;

			if (data == 0)
			{
				break;
			}
		}
	}
}

// display number
void showNumber(uint8_t number, uint8_t orderLED, uint8_t dot)
{
	// Bit dot (first)
	showDot(dot);

	// Counter loop (second)
	for (uint8_t c = 0; c < NUM_SEGMENT; c++)
	{
		// If the rightmost bit is 0
		(~number & 0b1) ? set_zero() : set_one();
		number = number >> 1;
	}

	// Loop orderLED (third)
	for (uint8_t c = 0; c < NUM_SEGMENT + NUM_DOT; c++)
	{
		(1 == (orderLED & 0b1)) ? set_zero() : set_one();
		orderLED = orderLED >> 1;
	}

	display();
}

// show dot
void showDot(uint8_t dot)
{
	(dot == 1) ? set_one() : set_zero();
}

// set bit 1
void set_one(void)
{
	// DATA | DIO -> LOW
	PORTB &= ~(1 << DATA);
	// CLOCK | SH_CP -> LOW
	PORTB &= ~(1 << CLOCK);
	// CLOCK | SH_CP -> HIGH
	PORTB |= (1 << CLOCK);
	// DATA | DIO -> HIGH
	PORTB |= (1 << DATA);
}

// set bit 0
void set_zero(void)
{
	// DATA | DIO -> HIGH
	PORTB |= (1 << DATA);
	// CLOCK | SH_CP -> LOW
	PORTB &= ~(1 << CLOCK);
	// CLOCK | SH_CP -> HIGH
	PORTB |= (1 << CLOCK);
}

//bit display LED
void display(void)
{
	// LATCH | STCP -> LOW -> HIGH
	PORTB &= ~(1 << LATCH);
	PORTB |= (1 << LATCH);
}