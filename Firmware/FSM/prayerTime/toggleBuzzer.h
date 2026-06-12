/*
 * toggleBuzzer.h
 *
 * Created: 5/28/2026 8:21:49 PM
 *  Author: Admin
 */ 


#ifndef TOGGLEBUZZER_H_
#define TOGGLEBUZZER_H_

#include <stdint.h>

#include <stdbool.h>

typedef struct
{
	uint32_t previousMillis;
	uint32_t interval;
	uint8_t  counter;
	uint8_t  targetCounter;
	bool     active;
	bool     state;
} Buzzer_t;


void buzzerStart  (void);
void buzzerUpdate (uint32_t interval, uint8_t counter);


#endif /* TOGGLEBUZZER_H_ */