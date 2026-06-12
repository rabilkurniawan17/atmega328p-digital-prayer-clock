/*
 * settingPrayerOffset.c
 *
 * Created: 6/9/2026 7:30:28 PM
 *  Author: Admin
 */ 

#include "settingPrayerOffset.h"

static uint32_t gPreviousCounterDebounce;

void handleSettingOffset(PrayerTime *pPrayer, PrayerOffset_t *offset, PrayerTimeID id, uint16_t address)
{
  static Setting_state_e state = DISPLAY;
  switch (state)
  {
  case DISPLAY:
    display_onlyOnePrayerName(pPrayer, id);
    if (button_readUp() || button_readDown())
    {
      state = DEBOUNCE_CHECK;
      gPreviousCounterDebounce = millis();
    }
    break;
  case BUTTON_UP:
    *(((int8_t*)(offset)) + address) = eeprom_readByte(address) + 1;
    eeprom_writeByte(address, *(((int8_t*)(offset)) + address));
    state = DISPLAY;
    break;
  case BUTTON_DOWN:
    *(((int8_t*)(offset)) + address) = eeprom_readByte(address) - 1;
    eeprom_writeByte(address, *(((int8_t*)(offset)) + address));
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