/*
 * settingDate.c
 *
 * Created: 5/26/2026 9:30:36 PM
 *  Author: Admin
 */ 
#include "settingDate.h"

static uint32_t gPreviousCounterDebounce;

void handleSettingDate(ds3231_Time_t *pRtc)
{
  static Setting_state_e state = DISPLAY;
  switch (state)
  {
  case DISPLAY:
    if (delay_isDelayFinish())
    {
      display_date(pRtc->year, pRtc->month, pRtc->date);
    }
    else
    {
      display_hideDate(pRtc->year, pRtc->month);
    }

    if (button_readUp() || button_readDown())
    {
      state = DEBOUNCE_CHECK;
      gPreviousCounterDebounce = millis();
    }
    break;
  case BUTTON_UP:
    pRtc->date++;
    if (pRtc->date >= 31)
    {
      pRtc->date = 1;
    }
    state = DISPLAY;
    break;
  case BUTTON_DOWN:
    if (pRtc->date == 1)
    {
      pRtc->date = 31;
    }
    else
    {
      pRtc->date--;
    }
    state = DISPLAY;
    break;
  case DEBOUNCE_CHECK:
    if (millis() - gPreviousCounterDebounce < BUTTON_DEBOUNCE_SETTING)
    {
      break;
    }
    if (button_readUp())
    {
      state = BUTTON_UP;
    }
    else if (button_readDown())
    {
      state = BUTTON_DOWN;
    }
    else
    {
      state = DISPLAY;
    }
    break;
  }
}

void handleSettingMonth(ds3231_Time_t *pRtc)
{
  static Setting_state_e state = DISPLAY;
  switch (state)
  {
  case DISPLAY:
    if (delay_isDelayFinish())
    {
      display_date(pRtc->year, pRtc->month, pRtc->date);
    }
    else
    {
      display_hideMonth(pRtc->year, pRtc->date);
    }

    if (button_readUp() || button_readDown())
    {
      state = DEBOUNCE_CHECK;
      gPreviousCounterDebounce = millis();
    }
    break;
  case BUTTON_UP:
    pRtc->month++;
    if (pRtc->month >= 12)
    {
      pRtc->month = 1;
    }
    state = DISPLAY;
    break;
  case BUTTON_DOWN:
    if (pRtc->month == 1)
    {
      pRtc->month = 12;
    }
    else
    {
      pRtc->month--;
    }
    state = DISPLAY;
    break;
  case DEBOUNCE_CHECK:
    if (millis() - gPreviousCounterDebounce < BUTTON_DEBOUNCE_SETTING)
    {
      break;
    }
    if (button_readUp())
    {
      state = BUTTON_UP;
    }
    else if (button_readDown())
    {
      state = BUTTON_DOWN;
    }
    else
    {
      state = DISPLAY;
    }
    break;
  }
}

void handleSettingYear(ds3231_Time_t *pRtc)
{
  static Setting_state_e state = DISPLAY;
  switch (state)
  {
  case DISPLAY:
    if (delay_isDelayFinish())
    {
      display_date(pRtc->year, pRtc->month, pRtc->date);
    }
    else
    {
      display_hideYear(pRtc->month, pRtc->date);
    }

    if (button_readUp() || button_readDown())
    {
      gPreviousCounterDebounce = millis();
      state = DEBOUNCE_CHECK;
    }     
    break;
  case BUTTON_UP:
    pRtc->year++;
    if (pRtc->year >= 2500)
    {
      pRtc->year = 2000;
    }
    state = DISPLAY;
    break;
  case BUTTON_DOWN:
    if (pRtc->year <= 1900)
    {
      pRtc->year = 2000;
    }
    else
    {
      pRtc->year--;
    }
    state = DISPLAY;
    break;
  case DEBOUNCE_CHECK:
    if (millis() - gPreviousCounterDebounce < BUTTON_DEBOUNCE_SETTING)
    {
      break;
    }
    if (button_readUp())
    {
      state = BUTTON_UP;
    }
    else if (button_readDown())
    {
      state = BUTTON_DOWN;
    }
    else
    {
      state = DISPLAY;
    }
    break;
  }
}