/*
 * fsm.h
 *
 * Created: 5/21/2026 11:00:29 PM
 *  Author: Admin
 */ 


#ifndef FSM_H_
#define FSM_H_

#include "../Apps/prayertimes.h"
#include "../Drivers/ds3231.h"
#include "../FSM/offset.h"
#include <stdbool.h>

#define DELAY_BLINK_DISPLAY		500
#define DELAY_DEBOUNCE_CHECK	120

typedef enum{
	stateDisplay,
	stateSetting,
	stateDebounceSetting,
	statePrayerTime,
	stateOffset
}fsm_State_e;

typedef enum
{
	fsm_setting_hour,
	fsm_setting_minute,
	fsm_setting_date,
	fsm_setting_month,
	fsm_setting_year,
	fsm_setting_debounceCheck,
	fsm_exit_setting
}fsm_setting_e;

typedef enum
{
	fsm_settingOffset_imsak,
	fsm_settingOffset_subuh,
	fsm_settingOffset_zuhur,
	fsm_settingOffset_ashar,
	fsm_settingOffset_maghrib,
	fsm_settingOffset_isya,
	fsm_settingOffset_debounceCheck,
	fsm_exit_settingOffset
}fsm_settingOffset_e;

void fsm_handleStateDisplay     (ds3231_Time_t *pRtc, PrayerTime *pPrayer);
bool fsm_handleStateSetting     (ds3231_Time_t *pRtc, PrayerTime *pPrayer);
bool fsm_handleStatePrayerTime  (ds3231_Time_t *pRtc, PrayerTime *pPrayer, PrayerTimeID prayerId);
bool fsm_handleStateOffset      (PrayerTime *pPrayer, PrayerOffset_t *offset);

PrayerTimeID prayerTimeArriveId (ds3231_Time_t *pRtc ,PrayerTime *pPrayer);

#endif /* FSM_H_ */