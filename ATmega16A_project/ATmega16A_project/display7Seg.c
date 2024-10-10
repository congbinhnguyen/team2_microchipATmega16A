/*
 * display7Seg.c
 *
 * Created: 9/28/2024 11:43:08 PM
 *  Author: binhc
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "header1.h"
#include <util/delay.h>



void choseNumber(uint8_t number, uint8_t order)
{
	uint8_t c; //counter loop
	
	// no dot	
	PORTB=0b00000101;
	_delay_ms(0.1);
	PORTB=0b00000100;
	_delay_ms(0.1);
	PORTB=0b00000101;
	_delay_ms(0.1);
	PORTB=0b00000111;
	_delay_ms(0.1);
	
	// loop number
	for (c=0; c<7;c++)
	{
		if(1==(number & 0b1))
		{
			PORTB=0b00000110;
			_delay_ms(0.1);
			PORTB=0b00000111;
			_delay_ms(0.1);
		}
		else
		{
			PORTB=0b00000101;
			_delay_ms(0.1);
			PORTB=0b000100;
			_delay_ms(0.1);
			PORTB=0b00000101;
			_delay_ms(0.1);
			PORTB=0b00000111;
			_delay_ms(0.1);
		}
		number = number >> 1;
	}
	
	// loop order
	for (c=0; c<7;c++)
	{
		if(1==(order & 0b1))
		{
			PORTB=0b00000110;
			_delay_ms(0.1);
			PORTB=0b00000111;
			_delay_ms(0.1);
		}
		else
		{
			PORTB=0b00000101;
			_delay_ms(0.1);
			PORTB=0b000100;
			_delay_ms(0.1);
			PORTB=0b00000101;
			_delay_ms(0.1);
			PORTB=0b00000111;
			_delay_ms(0.1);
		}
		order = order >> 1;
	}
}

void converNumber(uint8_t* numberTemp, uint8_t* orderNumber)
{
	switch ( *orderNumber)
	{
		case 1:
			*orderNumber = LED1;
			break;
		case 2:
			*orderNumber = LED2;
			break;
		case 3:
			*orderNumber = LED3;
			break;
		case 4:
			*orderNumber = LED4;
			break;
		case 5:
			*orderNumber = LED5;
			break;
		case 6:
			*orderNumber = LED6;
			break;
		case 7:
			*orderNumber = LED7;
			break;
		case 8:
			*orderNumber = LED8;
			break;
	}
	
	switch(*numberTemp)
	{
		case 0:
			*numberTemp = _ZERO_;
			break;
			
		case 1:
			*numberTemp = _ONE_;
			break;
		
		case 2:
			*numberTemp = _TWO_;
			break;
		
		case 3:
			*numberTemp = _THREE_;
			break;
			
		case 4:
			*numberTemp = _FOUR_;
			break;
			
		case 5:
			*numberTemp = _FIVE_;
			break;
		
		case 6:
			*numberTemp = _SIX_;
			break;
		
		case 7:
			*numberTemp = _SEVEN_;
			break;
		
		case 8:
			*numberTemp = _EIGHT_;
			break;
		
		case 9:
			*numberTemp = _NINE_;
			break;
		
	}
	
}

/*
void devideNumber(uint32_t number, uint8_t	* orderNumber, uint8_t	* numberTemp)
{
	if(number>=0 && number <=9)
	{
		*numberTemp = number;
		*orderNumber = 1;
		converNumber(&numberTemp, &orderNumber);
		choseNumber(numberTemp, orderNumber);
	}
	
}
*/