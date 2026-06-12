/*
 * fsm.c
 *
 * Created: 5/21/2026 11:00:42 PM
 *  Author: Admin
 */ 
#include "fsm.h"
#include "../FSM/delay.h"
#include "../FSM/setting/settingTime.h"
#include "../FSM/setting/settingDate.h"
#include "../FSM/setting/settingPrayerOffset.h"
#include "../Display/display.h"
#include "../Drivers/button.h"
#include "../Drivers/timer0.h"
#include "../Display/uart.h"

static uint32_t gPreviousCounterDebounce;

PrayerTimeID prayerTimeArriveId(ds3231_Time_t *pRtc ,PrayerTime *pPrayer)
{
  uint8_t rtcHour   = pRtc->hour;
  uint8_t rtcMinute = pRtc->minute;

  PrayerTimeID prayerId[] =
  {
      PRAYER_IMSAK,
      PRAYER_FAJR,
      PRAYER_DHUHR,
      PRAYER_ASR,
      PRAYER_MAGHRIB,
      PRAYER_ISHA,
  };

  for (int i = 0; i < sizeof(prayerId)/sizeof(prayerId[0]); i++)
  {
    PrayerTime pPrayerBuff = pPrayer[prayerId[i]];

    if (pPrayerBuff.hour == rtcHour && pPrayerBuff.minute == rtcMinute)
    {
      return prayerId[i];
    }
  }

  return PRAYER_NONE;
}

void fsm_handleStateDisplay(ds3231_Time_t *pRtc, PrayerTime *pPrayer)
{
  display_clock  (pRtc->hour, pRtc->minute);
  display_date   (pRtc->year, pRtc->month, pRtc->date);
  display_schedule (pPrayer);
}

static fsm_setting_e previousState;

static fsm_setting_e handleNextState(fsm_setting_e state)
{
  switch (state)
  {
  case fsm_setting_hour:   return fsm_setting_minute;
  case fsm_setting_minute: return fsm_setting_date;
  case fsm_setting_date:   return fsm_setting_month;
  case fsm_setting_month:  return fsm_setting_year;
  case fsm_setting_year:   return fsm_exit_setting;
  default:         return fsm_setting_hour;
  }
}

bool fsm_handleStateSetting(ds3231_Time_t *pRtc, PrayerTime *pPrayer)
{
  delay_toggleUpdate(DELAY_BLINK_DISPLAY);

  static fsm_setting_e state = fsm_setting_hour;

  switch(state)
  {
  case fsm_setting_hour:
    handleSettingHour(pRtc);

    if (button_readOke())
    {     
      gPreviousCounterDebounce = millis();
      state = fsm_setting_debounceCheck;
      previousState = fsm_setting_hour;
    }
    break;
  case fsm_setting_minute:
    handleSettingMinute(pRtc);

    if (button_readOke())
    {     
      gPreviousCounterDebounce = millis();
      state = fsm_setting_debounceCheck;
      previousState = fsm_setting_minute;
    }
    break;
  case fsm_setting_date:
    handleSettingDate(pRtc);

    if (button_readOke())
    {     
      gPreviousCounterDebounce = millis();
      state = fsm_setting_debounceCheck;
      previousState = fsm_setting_date;
    }
    break;
  case fsm_setting_month:
    handleSettingMonth(pRtc);

    if (button_readOke())
    {     
      gPreviousCounterDebounce = millis();
      state = fsm_setting_debounceCheck;
      previousState = fsm_setting_month;
    }
    break;
  case fsm_setting_year:
    handleSettingYear(pRtc);

    if (button_readOke())
    {     
      gPreviousCounterDebounce = millis();
      state = fsm_setting_debounceCheck;
      previousState = fsm_setting_year;
    }
    break;
  case fsm_setting_debounceCheck:   
    if (millis() - gPreviousCounterDebounce < DELAY_DEBOUNCE_CHECK)
    {
      break;
    }
    if (button_readOke())
    {
      state = handleNextState(previousState);
    }
    else
    {
      state = previousState;
    }
    break;
  case fsm_exit_setting:
    state = fsm_setting_hour;
    return true;
  }

  return false;
}

bool fsm_handleStatePrayerTime(ds3231_Time_t *pRtc, PrayerTime *pPrayer, PrayerTimeID prayerId)
{
  display_onlyOnePrayerName(pPrayer, prayerId);

  if (pRtc->minute != pPrayer[prayerId].minute)
  {   
    return true;
  }
  return false;
}

static fsm_settingOffset_e previousStateOffset;

static fsm_settingOffset_e handleNextOffsetState(fsm_settingOffset_e state)
{
  switch (state)
  {
  case fsm_settingOffset_imsak:   return fsm_settingOffset_subuh;
  case fsm_settingOffset_subuh:   return fsm_settingOffset_zuhur;
  case fsm_settingOffset_zuhur:   return fsm_settingOffset_ashar;
  case fsm_settingOffset_ashar:   return fsm_settingOffset_maghrib;
  case fsm_settingOffset_maghrib: return fsm_settingOffset_isya;
  case fsm_settingOffset_isya:    return fsm_exit_settingOffset;
  default:            return fsm_settingOffset_imsak;
  }
}

bool fsm_handleStateOffset(PrayerTime *pPrayer, PrayerOffset_t *offset)
{
  display_clockAndDateOff();
  static fsm_settingOffset_e state = fsm_settingOffset_imsak;
  switch (state)
  {
  case fsm_settingOffset_imsak:     
    handleSettingOffset(pPrayer, offset, PRAYER_IMSAK, 0);
    if (button_readOffset())
    {
      gPreviousCounterDebounce = millis();
      state = fsm_settingOffset_debounceCheck;
      previousStateOffset = fsm_settingOffset_imsak;
    }
    break;
  case fsm_settingOffset_subuh:
    handleSettingOffset(pPrayer, offset, PRAYER_FAJR, 1);
    if (button_readOffset())
    {
      gPreviousCounterDebounce = millis();
      state = fsm_settingOffset_debounceCheck;
      previousStateOffset = fsm_settingOffset_subuh;
    }
    break;
  case fsm_settingOffset_zuhur:
    handleSettingOffset(pPrayer, offset, PRAYER_DHUHR, 2);
    if (button_readOffset())
    {
      gPreviousCounterDebounce = millis();
      state = fsm_settingOffset_debounceCheck;
      previousStateOffset = fsm_settingOffset_zuhur;
    }
    break;
  case fsm_settingOffset_ashar:
    handleSettingOffset(pPrayer, offset, PRAYER_ASR, 3);
    if (button_readOffset())
    {
      gPreviousCounterDebounce = millis();
      state = fsm_settingOffset_debounceCheck;
      previousStateOffset = fsm_settingOffset_ashar;
    }
    break;
  case fsm_settingOffset_maghrib:
    handleSettingOffset(pPrayer, offset, PRAYER_MAGHRIB, 4);
    if (button_readOffset())
    {
      gPreviousCounterDebounce = millis();
      state = fsm_settingOffset_debounceCheck;
      previousStateOffset = fsm_settingOffset_maghrib;
    }
    break;
  case fsm_settingOffset_isya:
    handleSettingOffset(pPrayer, offset, PRAYER_ISHA, 5);
    if (button_readOffset())
    {
      gPreviousCounterDebounce = millis();
      state = fsm_settingOffset_debounceCheck;
      previousStateOffset = fsm_settingOffset_isya;
    }
    break;
  case fsm_exit_settingOffset:
    state = fsm_settingOffset_imsak;
    return true;
    break;
  case fsm_settingOffset_debounceCheck:
    if (millis() - gPreviousCounterDebounce < DELAY_DEBOUNCE_CHECK)
    {
      break;
    }
    if (button_readOffset())
    {
      state = handleNextOffsetState(previousStateOffset);
    }
    else
    {
      state = previousStateOffset;
    }
    break;    
  }
  return false;
}