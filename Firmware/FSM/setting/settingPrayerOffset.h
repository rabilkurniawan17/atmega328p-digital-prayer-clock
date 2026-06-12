/*
 * settingPrayerOffset.h
 *
 * Created: 6/9/2026 7:30:14 PM
 *  Author: Admin
 */ 


#ifndef SETTINGPRAYEROFFSET_H_
#define SETTINGPRAYEROFFSET_H_

#include "../../FSM/setting/settingConfig.h"


void handleSettingOffset(PrayerTime *pPrayer, PrayerOffset_t *offset, PrayerTimeID id, uint16_t address);


#endif /* SETTINGPRAYEROFFSET_H_ */