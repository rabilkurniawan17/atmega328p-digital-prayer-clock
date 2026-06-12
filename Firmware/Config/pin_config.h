/*
 * pin_config.h
 *
 * Created: 5/19/2026 9:12:10 PM
 *  Author: Admin
 */ 


#ifndef PIN_CONFIG_H_
#define PIN_CONFIG_H_

#include <avr/io.h>

//DS  / SDI  -> DATA
//STC / LOAD -> LATCH
//SHC / SCLK -> CLOCK

#define CLOCK_LATCH_DDR		DDRD
#define CLOCK_LATCH_PORT	PORTD
#define CLOCK_LATCH_PIN		PD3

#define CLOCK_DATA_DDR		DDRD
#define CLOCK_DATA_PORT		PORTD
#define CLOCK_DATA_PIN		PD2

#define CLOCK_CLK_DDR		DDRD
#define CLOCK_CLK_PORT		PORTD
#define CLOCK_CLK_PIN		PD4


#define DATE_LATCH_DDR		DDRD
#define DATE_LATCH_PORT		PORTD
#define DATE_LATCH_PIN		PD6

#define DATE_DATA_DDR		DDRD
#define DATE_DATA_PORT		PORTD
#define DATE_DATA_PIN		PD5

#define DATE_CLK_DDR		DDRD
#define DATE_CLK_PORT		PORTD
#define DATE_CLK_PIN		PD7


#define SCHEDULE_LATCH_DDR	DDRB
#define SCHEDULE_LATCH_PORT	PORTB
#define SCHEDULE_LATCH_PIN	PB1

#define SCHEDULE_DATA_DDR	DDRB
#define SCHEDULE_DATA_PORT	PORTB
#define SCHEDULE_DATA_PIN	PB2

#define SCHEDULE_CLK_DDR	DDRB
#define SCHEDULE_CLK_PORT	PORTB
#define SCHEDULE_CLK_PIN	PB0

#define BUTTON_PIN			PINC

#define BUTTON_SET_DDR		DDRC
#define BUTTON_SET_PORT		PORTC
#define BUTTON_SET_PIN		PC1

#define BUTTON_UP_DDR		DDRC
#define BUTTON_UP_PORT		PORTC
#define BUTTON_UP_PIN		PC2

#define BUTTON_DOWN_DDR		DDRC
#define BUTTON_DOWN_PORT	PORTC
#define BUTTON_DOWN_PIN		PC3

#define BUTTON_OFFSET_DDR	DDRC
#define BUTTON_OFFSET_PORT	PORTC
#define BUTTON_OFFSET_PIN	PC0


#define LED_DDR				DDRB
#define LED_PORT			PORTB
#define LED_PIN				PB3

#define BUZZER_DDR			DDRB
#define BUZZER_PORT			PORTB
#define BUZZER_PIN			PB4


#endif /* PIN_CONFIG_H_ */