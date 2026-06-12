/*
 * settingTime.c
 *
 * Created: 5/26/2026 1:19:51 PM
 *  Author: Admin
 */ 

#include "settingTime.h"

static uint32_t gPreviousCounterDebounce;

void handleSettingHour(ds3231_Time_t *pRtc)
{
  static Setting_state_e state = DISPLAY; 
  switch (state)
  {
  case DISPLAY:
    if (delay_isDelayFinish())
    {
      display_clock(pRtc->hour, pRtc->minute);
    }
    else
    {
      display_hideHour(pRtc->minute);
    }

    if (button_readUp() || button_readDown())
    {
      state = DEBOUNCE_CHECK;
      gPreviousCounterDebounce = millis();
    }
    break;
  case BUTTON_UP:
    pRtc->hour ++;
    if (pRtc->hour >= 24)
    {
      pRtc->hour = 0;
    }
    state = DISPLAY;
    break;
  case BUTTON_DOWN:
    if (pRtc->hour == 0)
    {
      pRtc->hour = 23;
    }
    else
    {
      pRtc->hour--;
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

void handleSettingMinute(ds3231_Time_t *pRtc)
{ 
  static Setting_state_e state = DISPLAY; 
  switch (state)
  {
  case DISPLAY:
    if (delay_isDelayFinish())
    {
      display_clock(pRtc->hour, pRtc->minute);
    }
    else
    {
      display_hideMinute(pRtc->hour);
    }

    if (button_readUp() || button_readDown())
    {
      state = DEBOUNCE_CHECK;
      gPreviousCounterDebounce = millis();
    }
    break;
  case BUTTON_UP:
    pRtc->minute ++;
    if (pRtc->minute >= 60)
    {
      pRtc->minute = 0;
    }
    state = DISPLAY;
    break;
  case BUTTON_DOWN:
    if (pRtc->minute == 0)
    {
      pRtc->minute = 59;
    }
    else
    {
      pRtc->minute--;
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