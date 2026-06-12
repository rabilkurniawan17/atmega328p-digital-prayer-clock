/*
 * settingDate.h
 *
 * Created: 5/26/2026 9:30:25 PM
 *  Author: Admin
 */ 


#ifndef SETTINGDATE_H_
#define SETTINGDATE_H_

#include "../../FSM/setting/settingConfig.h"

void handleSettingDate  (ds3231_Time_t *pRtc);
void handleSettingMonth (ds3231_Time_t *pRtc);
void handleSettingYear  (ds3231_Time_t *pRtc);

#endif /* SETTINGDATE_H_ */