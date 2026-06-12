/*
 * display.c
 *
 * Created: 5/14/2026 10:25:02 PM
 *  Author: Admin
 */ 

#include "display.h"
#include "../Drivers/hc595shift.h"
#include "../Drivers/gpio.h"
#include "../Config/pin_config.h"
#include "../Display/uart.h"

//static const uint8_t digitMap[11] = {
//0x7E, //0111 1110 0
//0x0C, //0000 1100 1
//0xB6, //1011 0110 2
//0x9E, //1001 1110 3
//0xCC, //1100 1100 4
//0xDA, //1101 1010 5
//0xFA, //1111 1010 6
//0x0E, //0000 1110 7
//0xFE, //1111 1110 8
//0xDE, //1101 1110 9
//0x00  //0000 0000 0
//};

static const uint8_t digitMap[11] = {
    0x3F, //0011 1111 0
    0x06, //0000 0110 1
    0x5B, //0101 1101 2
    0x4F, //0100 1111 3
    0x66, //0110 0110 4 
    0x6D, //0110 1101 5
    0x7D, //0111 1101 6
    0x07, //0000 0111 7
    0x7F, //0111 1111 8
    0x6F, //0110 1111 9
    0x00  //0000 0000 0
};
static const PrayerTimeID displayOrder[] =
{
    PRAYER_ISHA,
    PRAYER_MAGHRIB,
    PRAYER_ASR,
    PRAYER_DHUHR,
    PRAYER_FAJR,
    PRAYER_IMSAK
};

static void display_startSendData(display_StartSendData_t display)
{
  switch(display)
  {
  case CLOCK:
    CLOCK_LATCH_PORT &= ~(1<<CLOCK_LATCH_PIN);
    break;
  case DATE:
    DATE_LATCH_PORT &= ~(1<<DATE_LATCH_PIN);
    break;
  case SCHEDULE:
    SCHEDULE_LATCH_PORT &= ~(1<<SCHEDULE_LATCH_PIN);
    break;
  } 
}

static void display_stopSendData(display_StartSendData_t display)
{
  switch(display)
  {
  case CLOCK:
    CLOCK_LATCH_PORT |= (1<<CLOCK_LATCH_PIN);
    break;
  case DATE:
    DATE_LATCH_PORT |= (1<<DATE_LATCH_PIN);
    break;
  case SCHEDULE:
    SCHEDULE_LATCH_PORT |= (1<<SCHEDULE_LATCH_PIN);
    break;
  }
}

void Display_testSeventSegment(uint8_t digit)
{
  display_startSendData(CLOCK);

  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[digit]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[digit]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[digit]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[digit]);

  display_stopSendData(CLOCK);
}

void display_clock(uint8_t hour, uint8_t minute)
{
  uint8_t h1 = hour   / 10;
  uint8_t h2 = hour   % 10;

  uint8_t m1 = minute / 10;
  uint8_t m2 = minute % 10;


  display_startSendData(CLOCK);

  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[m1]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[m2]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[h1]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[h2]);

  display_stopSendData(CLOCK);
}

void display_date(uint16_t year, uint8_t month, uint8_t date)
{
  uint8_t y1 = (year / 1000) % 10;
  uint8_t y2 = (year / 100)  % 10;
  uint8_t y3 = (year / 10)   % 10;
  uint8_t y4 = year % 10;

  uint8_t m1 = month / 10;
  uint8_t m2 = month % 10;

  uint8_t d1 = date / 10;
  uint8_t d2 = date % 10;

  display_startSendData(DATE);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y2]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y3]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y4]);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[m1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[m2]);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[d1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[d2]);

  display_stopSendData(DATE);
}

void display_schedule(PrayerTime *pPrayer)
{
  display_startSendData(SCHEDULE);  

  for (int i = 0; i<6; i++) {
    PrayerTime p = pPrayer[displayOrder[i]];

    hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[p.hour / 10]);
    hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[p.hour % 10]);
    hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[p.minute / 10]);
    hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[p.minute % 10]);
  }

  display_stopSendData(SCHEDULE);
}

void display_hideMinute(uint8_t hour)
{
  uint8_t h1 = hour  / 10;
  uint8_t h2 = hour  % 10;

  display_startSendData(CLOCK);

  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[DIGIT_OFF]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[DIGIT_OFF]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[h1]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[h2]);

  display_stopSendData(CLOCK);
}

void display_hideHour(uint8_t minute)
{
  uint8_t m1 = minute / 10;
  uint8_t m2 = minute % 10;

  display_startSendData(CLOCK);

  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[m1]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[m2]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[DIGIT_OFF]);
  hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[DIGIT_OFF]);

  display_stopSendData(CLOCK);
}

void display_hideDate(uint16_t year, uint8_t month)
{
  uint8_t y1 = (year / 1000) % 10;
  uint8_t y2 = (year / 100)  % 10;
  uint8_t y3 = (year / 10)   % 10;
  uint8_t y4 = year % 10;

  uint8_t m1 = month / 10;
  uint8_t m2 = month % 10;

  display_startSendData(DATE);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y2]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y3]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y4]);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[m1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[m2]);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);

  display_stopSendData(DATE);
}

void display_hideMonth (uint16_t year, uint8_t date)
{
  uint8_t y1 = (year / 1000) % 10;
  uint8_t y2 = (year / 100)  % 10;
  uint8_t y3 = (year / 10)   % 10;
  uint8_t y4 = year % 10;

  uint8_t d1 = date / 10;
  uint8_t d2 = date % 10;

  display_startSendData(DATE);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y2]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y3]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[y4]);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[d1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[d2]);

  display_stopSendData(DATE);
}

void display_hideYear(uint8_t month, uint8_t date)
{ 
  uint8_t m1 = month / 10;
  uint8_t m2 = month % 10;

  uint8_t d1 = date / 10;
  uint8_t d2 = date % 10;

  display_startSendData(DATE);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[m1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[m2]);

  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[d1]);
  hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[d2]);

  display_stopSendData(DATE);
}

void display_onlyOnePrayerName(PrayerTime *pPrayer, PrayerTimeID prayerId)
{
  PrayerTime time = pPrayer[prayerId];

  display_startSendData(SCHEDULE);  
  for (int i=0; i<6; i++)
  {
    if (displayOrder[i] == prayerId)
    {
      hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[time.hour / 10]);
      hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[time.hour % 10]);
      hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[time.minute / 10]);
      hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[time.minute % 10]);
    }
    else
    {
      for (int i=0; i<4; i++)
      {
        hc595shift_shiftData(&SCHEDULE_DATA_PORT, SCHEDULE_DATA_PIN, &SCHEDULE_CLK_PORT, SCHEDULE_CLK_PIN, digitMap[DIGIT_OFF]);
      }
    }
  } 
  display_stopSendData(SCHEDULE);
}

void display_clockAndDateOff(void)
{
  display_startSendData(CLOCK);
  for (int i=0; i<4; i++)
  {
    hc595shift_shiftData(&CLOCK_DATA_PORT, CLOCK_DATA_PIN, &CLOCK_CLK_PORT, CLOCK_CLK_PIN, digitMap[DIGIT_OFF]);
  } 
  display_stopSendData(CLOCK);

  display_startSendData(DATE);
  for (int i=0; i<8; i++)
  {
    hc595shift_shiftData(&DATE_DATA_PORT, DATE_DATA_PIN, &DATE_CLK_PORT, DATE_CLK_PIN, digitMap[DIGIT_OFF]);
  } 
  display_stopSendData(DATE);
}