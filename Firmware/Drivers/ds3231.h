/*
 * ds3231.h
 *
 * Created: 5/13/2026 2:30:40 PM
 *  Author: Admin
 */ 


#ifndef DS3231_H_
#define DS3231_H_

#include <stdint.h>
#include "twi.h"

#define DS3231_ADDRESS	0x68

#define DS3231_SECONDS		0x00
#define DS3231_MINUTES		0x01
#define DS3231_HOURS		0x02
#define DS3231_DAY			0x03
#define DS3231_DATE			0x04
#define DS3231_MONTH		0x05
#define DS3231_YEAR			0x06

//list macro
#define TIME_LIST \
	TIME_DATA(second, SECONDS) \
	TIME_DATA(minute, MINUTES) \
	TIME_DATA(hour,   HOURS)   \
	TIME_DATA(day,    DAY)     \
	TIME_DATA(date,   DATE)    \
	TIME_DATA(month,  MONTH)   


typedef struct
{
	uint16_t	year;
	uint8_t		month;
	uint8_t		date;
	uint8_t		day;
	uint8_t		hour;
	uint8_t		minute;
	uint8_t		second;
}ds3231_Time_t;

void ds3231_getTime(ds3231_Time_t *time);
void ds3231_setTime(ds3231_Time_t *time);

#endif /* DS3231_H_ */