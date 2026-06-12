/*
 * offset.c
 *
 * Created: 6/12/2026 10:20:07 AM
 *  Author: Admin
 */ 

#include "offset.h"

static const PrayerTimeID settingOrder[] = {
    PRAYER_IMSAK,
    PRAYER_FAJR,
    PRAYER_DHUHR,
    PRAYER_ASR,
    PRAYER_MAGHRIB,
    PRAYER_ISHA
};

void offset_prayerTime(PrayerTime *pPrayer, PrayerOffset_t *offset)
{
  int16_t totalPrayerTime;
  for (int i=0; i<sizeof(settingOrder); i++)
  {
    totalPrayerTime = (pPrayer[settingOrder[i]].hour * 60) + pPrayer[settingOrder[i]].minute + *(((int8_t*)(offset)) + i);

    if (totalPrayerTime < 0)
    {
      totalPrayerTime += 1440;
    }
    if (totalPrayerTime >= 1440)
    {
      totalPrayerTime -= 1440;
    }
    pPrayer[settingOrder[i]].hour   = totalPrayerTime / 60;
    pPrayer[settingOrder[i]].minute = totalPrayerTime % 60;
  }
}