/*
 * processNumber.c
 *
 *  Author: binh + thai
 */

#include "..\header1.h"

#define MIN_VALUE 0
#define MAX_VALUE 999999
#define NUM_DIGITS 8 // Number of displayable digits

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