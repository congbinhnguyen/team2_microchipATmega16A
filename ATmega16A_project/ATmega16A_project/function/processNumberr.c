/*
 * processNumberr.c
 *
 * Created: 10/11/2024 9:24:35 AM
 *  Author: binhc
 */ 


#include "..\header1.h"

void processNumber (uint32_t data)  
{
	uint8_t number;
	uint8_t orderLED;
	uint8_t counter; //counter loop
	uint8_t dot = 0;
	uint32_t devisor=1;
	
	
	if(data>=0 && data <=9)
	{
		number = data;
		orderLED = 1;
		convertNumber(&number, &orderLED);
		showNumber(number, orderLED, 0);
	}
	else if(data >=10 && data <=99)
	{
		for (counter = 1; counter <=2; counter++)
		{
			number = (data / devisor) % 10;
			devisor *=10;
			orderLED = counter;
			convertNumber(&number, &orderLED);
			showNumber(number, orderLED, 0);
		}
	}
	else if(data >=100 && data <=999)
	{
		for (counter = 1; counter <=3; counter++)
		{
			number = (data / devisor) % 10;
			devisor *=10;
			orderLED = counter;
			convertNumber(&number, &orderLED);
			showNumber(number, orderLED, 0);
		}	
		
	}
	else if (data >=1000 && data <=9999)
	{
		for (counter = 1; counter <=4; counter++)
		{
			number = (data / devisor) % 10;
			devisor *=10;
			orderLED = counter;
			if (counter == 4)
			{
				dot = 1;
			}
			convertNumber(&number, &orderLED);
			showNumber(number, orderLED, dot);
		}
	}
	else if (data >=10000 && data <= 99999)
	{
		for (counter = 1; counter <=5; counter++)
		{
			number = (data / devisor) % 10;
			devisor *=10;
			orderLED = counter;
			if (counter == 4)
			{
				dot = 1;
			}
			convertNumber(&number, &orderLED);
			showNumber(number, orderLED, dot);
			dot = 0;
		}
	}
	else if(data>=100000 && data <= 999999)
	{
		for (counter = 1; counter <=6; counter++)
		{
			number = (data / devisor) % 10;
			devisor *=10;
			orderLED = counter;
			if (counter == 4)
			{
				dot = 1;
			}
			convertNumber(&number, &orderLED);
			showNumber(number, orderLED, dot);
			dot = 0;
		}
	}
	else if (data >=1000000 && data <=9999999)
	{
		for (counter = 1; counter <=7; counter++)
		{
			number = (data / devisor) % 10;
			devisor *=10;
			orderLED = counter;
			if (counter == 7 || counter == 4)
			{
				dot = 1;
			}
			convertNumber(&number, &orderLED);
			showNumber(number, orderLED, dot);
			dot = 0;
		}
	}
	else if (data >= 10000000 && data <=99999999)
	{
		for (counter = 1; counter <=8; counter++)
		{
			number = (data / devisor) % 10;
			devisor *=10;
			orderLED = counter;
			if (counter == 7 || counter == 4)
			{
				dot = 1;
			}
			convertNumber(&number, &orderLED);
			showNumber(number, orderLED, dot);
			dot = 0;
		}
	}
	else
	{
		//error
	}
	
	// reset status DOT
	
	dot = 0;
	
	
}