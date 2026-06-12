#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init			 (uint16_t   myubr);
void uart_transmit		 (uint8_t    data);
void uart_transmit16	 (uint16_t   data);
void uart_transmitString (const char *str);
void uart_transmitHex    (uint8_t    data);
void uart_transmitAscii  (uint16_t   data);

#endif