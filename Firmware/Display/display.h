/*
 * display.h
 *
 * Created: 5/14/2026 10:24:48 PM
 *  Author: Admin
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include "../Apps/prayertimes.h"

#define DIGIT_OFF 10

typedef enum{
	CLOCK,
	DATE,
	SCHEDULE
}display_StartSendData_t;

void display_clock	     (uint8_t hour, uint8_t minute);
void display_date	     (uint16_t year, uint8_t month, uint8_t date);
void display_schedule    (PrayerTime *Prayer);

void display_hideMinute  (uint8_t hour);
void display_hideHour    (uint8_t minute);

void display_hideDate    (uint16_t year, uint8_t month);
void display_hideMonth   (uint16_t year, uint8_t date);
void display_hideYear    (uint8_t month, uint8_t date);

void display_onlyOnePrayerName (PrayerTime *pPrayer, PrayerTimeID prayerId);
void Display_testSeventSegment (uint8_t digit);
void display_clockAndDateOff   (void);
#endif /* DISPLAY_H_ */