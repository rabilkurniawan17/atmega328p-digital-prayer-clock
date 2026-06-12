#ifndef PRAYERTIMES_H
#define PRAYERTIMES_H

#include <stdint.h>

/* ===================== ENUM ===================== */

typedef enum
{	
	PRAYER_IMSAK,
	PRAYER_FAJR,
	PRAYER_SUNRISE,
	PRAYER_DHUHR,
	PRAYER_ASR,
	PRAYER_SUNSET,
	PRAYER_MAGHRIB,
	PRAYER_ISHA,
	PRAYER_COUNT,
	
	PRAYER_NONE = 255
} PrayerTimeID;

typedef enum
{
	METHOD_MWL,
	METHOD_EGYPT,
	METHOD_MAKKAH,
	METHOD_KARACHI,
	METHOD_ISNA
} PrayerMethod;

typedef enum
{
	ASR_SHAFII = 1,
	ASR_HANAFI = 2
} AsrMethod;

/* ===================== STRUCT ===================== */

typedef struct
{
	uint8_t hour;
	uint8_t minute;
} PrayerTime;

/* ===================== API ===================== */

void prayer_set_method(PrayerMethod method);

void prayer_set_asr_method(AsrMethod method);

void prayer_calculate(
uint16_t year,
uint8_t month,
uint8_t day,
double latitude,
double longitude,
double timezone,
PrayerTime result[]
);

#endif