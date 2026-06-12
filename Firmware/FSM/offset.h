/*
 * offset.h
 *
 * Created: 6/12/2026 10:19:54 AM
 *  Author: Admin
 */ 


#ifndef OFFSET_H_
#define OFFSET_H_

#include <stdint.h>
#include "../Apps/prayertimes.h"

typedef struct
{
	int8_t imsak;
	int8_t subuh;
	int8_t zuhur;
	int8_t ashar;
	int8_t maghrib;
	int8_t isya;
}PrayerOffset_t;

void offset_prayerTime(PrayerTime *pPrayer, PrayerOffset_t *offset);


#endif /* OFFSET_H_ */