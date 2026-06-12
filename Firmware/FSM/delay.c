/*
 * delay.c
 *
 * Created: 5/26/2026 12:54:36 PM
 *  Author: Admin
 */ 
#include "delay.h"
#include "../Drivers/timer0.h"

static bool		bToggle;
static uint32_t previousCounterDelay;

void delay_toggleUpdate(uint32_t toggleTime)
{
	if (millis() - previousCounterDelay >= toggleTime)
	{
		bToggle = !bToggle;
		previousCounterDelay = millis();
	}
}

bool delay_isDelayFinish(void)
{
	return bToggle;
}