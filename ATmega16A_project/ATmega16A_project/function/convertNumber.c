/*
 * convertNumber.c
 *
 * Created: 10/11/2024 9:05:31 AM
 *  Author: binhc
 */ 

#include "..\header1.h"

void convertNumber(uint8_t * number, uint8_t * orderLED)
{
	switch ( *orderLED)
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
	
	switch(*number)
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
	
}
