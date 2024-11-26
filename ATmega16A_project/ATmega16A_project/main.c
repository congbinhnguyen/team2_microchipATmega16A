/*
 * ATmega16A_project.c
 *
 * Created: 9/28/2024 11:42:09 PM
 * Author : binhc + thai
 */

#include "LEDdisplay.h"
#include "PINsetup.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define F_CPU 1000000UL // 1MHz clock frequency

void setup(void);
void enable_overflow_interrupt(void);
void disable_overflow_interrupt(void);

volatile uint32_t object_counter = 0;
volatile uint8_t object_in_detected = 0;
volatile uint8_t object_out_detected = 0;

volatile uint8_t buzzed_in = 0;
volatile uint8_t buzzed_count_in = 0;

volatile uint8_t buzzed_out = 0;
volatile uint8_t buzzed_count_out = 0;

volatile uint8_t count_in_enabled = 1;
volatile uint8_t count_out_enabled = 1;
volatile uint8_t buzzer_enabled = 1;

volatile uint8_t received_command = 0; // Store the received command
uint32_t onlyChange;

ISR(INT0_vect)
{
	if (count_in_enabled && !object_in_detected)
	{
		object_counter++;
		object_in_detected = 1;

		if (!buzzed_in && buzzer_enabled)
		{
			buzzed_in = 1;
			disable_overflow_interrupt();
			enable_overflow_interrupt();
		}
	}
}

ISR(INT1_vect)
{
	if (count_out_enabled && object_counter > 0 && !object_out_detected)
	{
		object_counter--;
		object_out_detected = 1;

		if (!buzzed_out && buzzer_enabled)
		{
			buzzed_out = 1;
			disable_overflow_interrupt();
			enable_overflow_interrupt();
		}
	}
}

ISR(TIMER1_OVF_vect)
{
	// Increment counters for in and out buzzed events
	if (buzzed_in)
	{
		buzzed_count_in++;
		PORTD |= (1 << BUZZER);

		if (buzzed_count_in >= 2)
		{
			PORTD &= ~(1 << BUZZER);
			buzzed_in = 0;
			disable_overflow_interrupt();
		}
	}

	if (buzzed_out)
	{
		buzzed_count_out++;
		PORTD |= (1 << BUZZER);

		if (buzzed_count_out >= 2)
		{
			PORTD &= ~(1 << BUZZER);
			buzzed_out = 0;
			disable_overflow_interrupt();
		}
	}
}

ISR(USART_RXC_vect)
{
	uint8_t command = UDR;
	if (command == 1 || command == 2 || command == 3)
	{
		received_command = command;
	}
}

void UART_Init(unsigned int baud_rate)
{
	unsigned int ubrr = F_CPU / 16 / baud_rate - 1;

	// set up baue rate
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;

	// turn on UART and UART interrupt
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
	
	// config 8-bit data, 1 stop bit
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void UART_TransmitByte(uint8_t data)
{
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = data;
}

void UART_TransmitUint32(uint32_t data)
{
	for (int i = 0; i < 4; i++)
	{
		UART_TransmitByte((uint8_t)(data >> (i * 8)));
	}
}

uint8_t UART_ReceiveByte(void)
{
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}

int main(void)
{
	setup();
	UART_Init(9600);

	while (1)
	{
		// handling switch state 
		if (received_command != 0)
		{
			switch (received_command)
			{
			case 1:
				count_in_enabled = !count_in_enabled;
				break;
			case 2:
				count_out_enabled = !count_out_enabled;
				break;
			case 3:
				buzzer_enabled = !buzzer_enabled;
				break;
			default:
				break;
			}
			received_command = 0;
		}

		// Check if the object is still present
		if (PIND & (1 << PROX_IN)) // If sensor no longer detects the object (high signal)
		{
			object_in_detected = 0;
			if (!(PORTD & (1 << BUZZER))) // if buzzer isn't doing
			{
				buzzed_count_in = 0;
			}
		}

		if (PIND & (1 << PROX_OUT)) // If sensor no longer detects the object (high signal)
		{
			object_out_detected = 0;
			if (!(PORTD & (1 << BUZZER))) // if buzzer isn't doing
			{
				buzzed_count_out = 0;
			}
		}

		processNumber(object_counter);
		if (onlyChange != object_counter)
		{
			UART_TransmitByte((uint8_t)object_counter);
		}
		onlyChange = object_counter;
	}

	return 0;
}

void setup(void)
{
	DDRB |= (1 << CLOCK);
	DDRB |= (1 << DATA);
	DDRB |= (1 << LATCH);
	DDRD &= ~(1 << PROX_IN);
	DDRD &= ~(1 << PROX_OUT);
	DDRD |= (1 << BUZZER);

	// set up interrupt
	GICR |= (1 << INT0) | (1 << INT1);
	MCUCR |= (1 << ISC01) | (1 << ISC11); // Falling edge trigger

	// Timer1
	TCCR1A = 0x00;
	TCCR1B |= (1 << CS10);

	sei();
}

void enable_overflow_interrupt(void)
{
	// Initialize Timer1 register
	TCNT1 = 0;
	// Enable Timer1 overflow interrupt
	TIMSK |= (1 << TOIE1);
}

void disable_overflow_interrupt(void)
{
	// Disable Timer1 overflow interrupt
	TIMSK &= ~(1 << TOIE1);
}
