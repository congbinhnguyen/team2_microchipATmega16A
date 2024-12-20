/*
 * LEDdisplay.h
 *
 * Created: 9/28/2024 11:42:27 PM
 *  Author: binhc
 */ 

#ifndef __LED_DISPLAY_
#define __LED_DISPLAY_

#include <avr/io.h>
#include <stdint.h>
#include "PINsetup.h"

#define MIN_VALUE 0
#define MAX_VALUE 999999
#define NUM_DIGITS 8 // Number of displayable digits
#define NUM_SEGMENT 7 // Number of segments
#define NUM_DOT 1 // Number of dot

//Number define
#define		_ZERO_		0b1111110
#define		_ONE_		0b0110000
#define		_TWO_		0b1101101
#define		_THREE_		0b1111001
#define		_FOUR_		0b0110011
#define		_FIVE_		0b1011011
#define		_SIX_		0b1011111
#define		_SEVEN_		0b1110000
#define		_EIGHT_		0b1111111
#define		_NINE_		0b1111011

// ERROR notion define
#define		_E_			0b1001111
#define		_R_			0b1100110
#define		_O_			0b1111110

//orderLED define
#define		LED8		0b00000001
#define		LED7		0b00000010
#define		LED6		0b00000100
#define		LED5		0b00001000
#define		LED4		0b00010000
#define		LED3		0b00100000
#define		LED2		0b01000000
#define		LED1		0b10000000

//declare functions
void displayError();
void number2bin(uint8_t *number, uint8_t *orderLED);
void processNumber(uint32_t data);
void showNumber(uint8_t number, uint8_t orderLED, uint8_t dot);
void showDot(uint8_t dot);
void set_one(void);
void set_zero(void);
void display(void);

#endif /* HEADER1_H_ */