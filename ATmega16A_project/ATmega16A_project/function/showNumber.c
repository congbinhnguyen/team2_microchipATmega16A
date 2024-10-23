/*
 * showNumber.c
 *
 * Created: 9/28/2024 11:43:08 PM
 *  Author: binhc
 */

#include "..\header1.h"

#define CLOCK PB0 // SH-CP | SCLK (Shift Clock)
#define DATA PB1  // DS | DIO
#define LATCH PB2 // ST-CP (Storage Clock) | RCLK (Register Clock)
#define NUM_SEGMENT 7 // Number of segments
#define NUM_DOT 1 // Number of dot

void showDot(uint8_t dot);
void set_one(void);
void set_zero(void);
void display(void);

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

void showDot(uint8_t dot)
{
	(dot == 1) ? set_one() : set_zero();
}

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

void set_zero(void)
{
	// DATA | DIO -> HIGH
	PORTB |= (1 << DATA);
	// CLOCK | SH_CP -> LOW
	PORTB &= ~(1 << CLOCK);
	// CLOCK | SH_CP -> HIGH
	PORTB |= (1 << CLOCK);
}

void display(void)
{
	// LATCH | STCP -> LOW -> HIGH
	PORTB &= ~(1 << LATCH);
	PORTB |= (1 << LATCH);
}