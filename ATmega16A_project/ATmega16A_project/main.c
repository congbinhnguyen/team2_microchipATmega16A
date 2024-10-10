/*
 * ATmega16A_project.c
 *
 * Created: 9/28/2024 11:42:09 PM
 * Author : binhc
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "header1.h"
#include <util/delay.h>


int main(void)
{
	DDRB = 0b00000111;
	
// 	temp
// 		uint8_t counter;
// 		for(counter = 0; counter <=7; counter ++)
// 		{
// 			PORTB=0b00000101;
// 			_delay_ms(0.1);
// 			PORTB=0b00000100;
// 			_delay_ms(0.1);
// 			PORTB=0b00000101;
// 			_delay_ms(0.1);
// 			PORTB=0b00000111;
// 			_delay_ms(0.1);
// 			
// 		}
// 		
// 		
// 		
// 		//	export data
// 		PORTB = 0b00000011;
// 		_delay_ms(0.1);
// 		PORTB = 0b00000111;
// 		_delay_ms(0.1);
// 			
// 		
// 		
// 		
// 		
// 		
// 		
// 		
// 		
// 		



	while (1) 
    {
		/*devideNumber(8, &numberTemp, &orderNumber);*/
 		//	export data
		PORTB = 0b00000011;
		_delay_ms(0.1);
		PORTB = 0b00000111;
		_delay_ms(0.1);
    }
	
	return 0;
}

