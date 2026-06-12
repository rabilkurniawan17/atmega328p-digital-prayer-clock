/*
 * settingConfig.h
 *
 * Created: 5/26/2026 9:33:41 PM
 *  Author: Admin
 */ 


#ifndef SETTINGCONFIG_H_
#define SETTINGCONFIG_H_


#include "../../Drivers/ds3231.h"
#include "../../Apps/prayertimes.h"
#include "../../Display/display.h"
#include "../../Drivers/button.h"
#include "../../FSM/delay.h"
#include "../../Drivers/timer0.h"
#include "../../Drivers/eeprom.h"

#define BUTTON_DEBOUNCE_SETTING	120

typedef enum
{
	DISPLAY,
	BUTTON_UP,
	BUTTON_DOWN,
	DEBOUNCE_CHECK
}Setting_state_e;

#endif /* SETTINGCONFIG_H_ */