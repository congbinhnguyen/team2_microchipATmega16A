/*
 * proccess_interrupt.h
 *
 * Created: 11/9/2024 11:56:33 PM
 *  Author: binhc
 */ 


#ifndef PROCCESS_INTERRUPT_H_
#define PROCCESS_INTERRUPT_H_

#include "PINsetup.h"
#include "LEDdisplay.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

volatile uint32_t object_counter = 0;
volatile uint8_t object_in_detected = 0;
volatile uint8_t object_out_detected = 0;

volatile uint8_t buzzed_in = 0;
volatile uint8_t buzzed_count_in = 0;

volatile uint8_t buzzed_out = 0;
volatile uint8_t buzzed_count_out = 0;

void demo(void);
void enable_overflow_interrupt(void);
void disable_overflow_interrupt(void);

#endif /* PROCCESS_INTERRUPT_H_ */