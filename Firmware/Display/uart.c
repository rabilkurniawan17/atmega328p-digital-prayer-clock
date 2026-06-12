#include "UART.h"
#include <avr/io.h>
#include <stdlib.h>

static char bufer[10];

void uart_init (uint16_t myubr)
{
	//set baud rate
	UBRR0H = (uint8_t) (myubr>>8);
	UBRR0L = (uint8_t) myubr;

	//enable TX
	UCSR0B = (1<<TXEN0);

	//set frame format: 8 data and 1 stop bit
	UCSR0C = (3<<UCSZ00);
}

void uart_transmit(uint8_t data)
{
	//wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));

	//put data into buffer and send data
	UDR0 = data;
}

void uart_transmit16(uint16_t data)
{
	//wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));

	//put data into buffer and send data
	UDR0 =(uint8_t) (data>>8);

	//wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));

	//put data into buffer and send data
	UDR0 =(uint8_t) data;
}

void uart_transmitString(const char *str)
{
	while(*str)
	{
		uart_transmit(*str++);
	}
}

void uart_transmitHex(uint8_t data)
{
	const char hex[] = "0123456789ABCDEF";

	uart_transmit(hex[(data >> 4) & 0x0F]);
	uart_transmit(hex[data & 0x0F]);
}

void uart_transmitAscii (uint16_t data)
{
	itoa(data, bufer, 10);
	uart_transmitString(bufer);
}