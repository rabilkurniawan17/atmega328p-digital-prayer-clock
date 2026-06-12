
/*
 * JWS 7 Segment ATMega328p.c
 *
 * Created: 5/13/2026 1:21:25 PM
 * Author : Rabil Kurniawan
 */ 
#include <avr/io.h>
#include "Config/system_config.h"


PrayerTime       gPrayer[PRAYER_COUNT];
ds3231_Time_t    gRtc;
PrayerTimeID     gPrayerId;
PrayerOffset_t   gOffset;
static Counter_t previousCounter;

int main(void)
{  
  gRtc.hour   = 8;
  gRtc.minute = 47;
  gRtc.second = 0;
  gRtc.day    = 1;
  gRtc.date   = 5;
  gRtc.month  = 6;
  gRtc.year   = 2026;

  uart_init(myubrr);
  twi_init(100000);
  gpio_init();
  led_init();
  timer0_init();

  //ds3231_setTime(&gRtc);  
  ds3231_getTime(&gRtc);

  prayer_set_method(METHOD_MWL);
  prayer_set_asr_method(ASR_SHAFII);
  prayer_calculate(gRtc.year, gRtc.month, gRtc.date, latitude, longitude, timeZone, gPrayer);

  eeprom_readBlock(&gOffset, START_ADDRESS_OFFSET_EEPROM, sizeof(gOffset));
  while (1)
  {
    if (gRtc.date != previousCounter.previousDate)
    {
      previousCounter.previousDate = gRtc.date;
      prayer_calculate(gRtc.year, gRtc.month, gRtc.date, latitude, longitude, timeZone, gPrayer);
      eeprom_readBlock(&gOffset, START_ADDRESS_OFFSET_EEPROM, sizeof(gOffset));
      offset_prayerTime(gPrayer, &gOffset);
    }

    static fsm_State_e state = stateDisplay;
    switch(state)
    {
    case stateDisplay:
      fsm_handleStateDisplay(&gRtc, gPrayer);

      if (millis() - previousCounter.counter_rtc >= DELAY_UPDATE_RTC)
      {
        previousCounter.counter_rtc = millis();
        ds3231_getTime(&gRtc);
      }

      if (millis() - previousCounter.counter_prayerTime >= DELAY_CHECKING_PRAYERTIME)
      {
        previousCounter.counter_prayerTime = millis();

        gPrayerId = prayerTimeArriveId(&gRtc, gPrayer);
        if (gPrayerId != PRAYER_NONE)
        {
          buzzerStart();
          state = statePrayerTime;
        }
      }

      if(button_readOke())
      {
        state = stateDebounceSetting;
        previousCounter.Counter_debounce = millis();
      }

      if (button_readOffset())
      {
		state = stateDebounceSetting;
		previousCounter.Counter_debounce = millis();
      }
      break;

    case stateSetting:
      if (fsm_handleStateSetting(&gRtc, gPrayer))
      {
        ds3231_setTime(&gRtc);
        state = stateDisplay;
      }
      break;

    case statePrayerTime:
      buzzerUpdate(1000, 7);

      ds3231_getTime(&gRtc);
      if (fsm_handleStatePrayerTime(&gRtc, gPrayer, gPrayerId))
      {
        state = stateDisplay;
      }
      break;

    case stateOffset:	  
	  prayer_calculate(gRtc.year, gRtc.month, gRtc.date, latitude, longitude, timeZone, gPrayer);
	  eeprom_readBlock(&gOffset, START_ADDRESS_OFFSET_EEPROM, sizeof(gOffset));
	  offset_prayerTime(gPrayer, &gOffset);
	  if (fsm_handleStateOffset(gPrayer, &gOffset))
	  {
		state = stateDisplay;
	  }	  
	  break;
	  
	case stateDebounceSetting:
      if((millis() - previousCounter.Counter_debounce < BUTTON_DEBOUNCE_TIME_CHECK))
      {
        break;
      }
      if (button_readOke())
      {
        state = stateSetting;
      }
	  else if (button_readOffset())
	  {
		  state = stateOffset;
	  }
      else
      {
        state = stateDisplay;
      }
      break;
    }
  }
}

