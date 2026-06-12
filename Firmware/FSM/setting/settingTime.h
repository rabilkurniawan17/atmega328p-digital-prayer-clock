/*
 * settingTime.h
 *
 * Created: 5/26/2026 1:19:36 PM
 *  Author: Admin
 */ 


#ifndef SETTINGTIME_H_
#define SETTINGTIME_H_

#include "../../FSM/setting/settingConfig.h"

void handleSettingHour   (ds3231_Time_t *pRtc);
void handleSettingMinute (ds3231_Time_t *pRtc);



#endif /* SETTINGTIME_H_ */