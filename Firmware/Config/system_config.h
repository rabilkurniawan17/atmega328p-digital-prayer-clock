/*
 * system_config.h
 *
 * Created: 5/13/2026 2:29:38 PM
 *  Author: Admin
 */ 


#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#define F_CPU 16000000UL

#include "../Drivers/led.h"
#include "../Apps/prayertimes.h"
#include "../Drivers/ds3231.h"
#include "../Display/display.h"
#include "../Drivers/timer0.h"
#include "../Display/uart.h"
#include "../FSM/fsm.h"
#include "../Drivers/button.h"
#include "../FSM/prayerTime/toggleBuzzer.h"
#include "../FSM/prayerTime/toggleBuzzer.h"
#include "../FSM/setting/settingPrayerOffset.h"
#include "../Drivers/eeprom.h"
#include "../FSM/offset.h"

#include <stdint.h>

#define baud		(9600)
#define myubrr		((F_CPU/16)/baud)-1

#define latitude	(2.0839648)
#define longitude	(100.6462629)
#define timeZone	(7)

#define BUTTON_DEBOUNCE_TIME_CHECK  (120)
#define DELAY_CHECKING_PRAYERTIME   (1000)
#define DELAY_UPDATE_RTC		    (1000)
#define START_ADDRESS_OFFSET_EEPROM (0)

typedef struct
{
	uint32_t Counter_debounce;
	uint32_t counter_prayerTime;
	uint32_t counter_rtc;	
	uint8_t  previousDate;
}Counter_t;


#endif /* SYSTEM_CONFIG_H_ */