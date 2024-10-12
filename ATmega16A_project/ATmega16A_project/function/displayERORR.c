/*
 * displayERORR.c
 *
 * Created: 10/11/2024 9:32:10 AM
 *  Author: binhc
 */ 


#include "..\header1.h"

//ERROR 1: OUT LIMIT NUMBER
void displayError()
{
	showNumber(_E_, LED6, 0);
	showNumber(_R_, LED5, 0);
	showNumber(_R_, LED4, 0);
	showNumber(_O_, LED3, 0);
	showNumber(_R_, LED2, 0);
}