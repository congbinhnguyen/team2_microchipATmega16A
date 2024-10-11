/*
 * display7Seg.c
 *
 * Created: 9/28/2024 11:43:08 PM
 *  Author: binhc
 */ 

#include "..\header1.h"


void showDot(uint8_t dot)
{
	if(dot ==1) 		// show dot		
	{
		PORTB=0b00000101;
		_delay_ms(TIMELED);
		PORTB=0b000100;
		_delay_ms(TIMELED);
		PORTB=0b00000101;
		_delay_ms(TIMELED);
		PORTB=0b00000111;
		_delay_ms(TIMELED);
	}
	else
	{
		PORTB=0b00000110;
		_delay_ms(TIMELED);
		PORTB=0b00000111;
		_delay_ms(TIMELED);
	}
}

void showNumber(uint8_t number, uint8_t orderLED, uint8_t dot)
{
	// bit dot
	showDot(dot);	
	
	uint8_t c; //counter loop
	for (c=0; c<7;c++)
	{
		if (~number & 0b1)
		{
			PORTB=0b00000110;
			_delay_ms(TIMELED);
			PORTB=0b00000111;
			_delay_ms(TIMELED);
		}
		else
		{
			PORTB=0b00000101;
			_delay_ms(TIMELED);
			PORTB=0b000100;
			_delay_ms(TIMELED);
			PORTB=0b00000101;
			_delay_ms(TIMELED);
			PORTB=0b00000111;
			_delay_ms(TIMELED);
		}
		number = number >> 1;
	}
	
	// loop orderLED
	for (c=0; c<=7;c++)
	{
		if(1==(orderLED & 0b1))
		{
			PORTB=0b00000110;
			_delay_ms(TIMELED);
			PORTB=0b00000111;
			_delay_ms(TIMELED);
		}
		else
		{
			PORTB=0b00000101;
			_delay_ms(TIMELED);
			PORTB=0b000100;
			_delay_ms(TIMELED);
			PORTB=0b00000101;
			_delay_ms(TIMELED);
			PORTB=0b00000111;
			_delay_ms(TIMELED);
		}
		orderLED = orderLED >> 1;
	}
	
	//	export data
	PORTB = 0b00000011;
	_delay_ms(TIMELED);
	PORTB = 0b00000111;
	_delay_ms(TIMELED);
}