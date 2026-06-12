/*
 * button.h
 *
 * Created: 5/22/2026 6:17:05 AM
 *  Author: Admin
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../Config/pin_config.h"
#include "gpio.h"


//Macro list
#define BUTTON_LIST \
	BUTTON_DATA(Oke,    SET_PIN)  \
	BUTTON_DATA(Up,     UP_PIN)   \
	BUTTON_DATA(Down,   DOWN_PIN) \
	BUTTON_DATA(Offset, OFFSET_PIN)
	
#define BUTTON_DATA(buttonHandle, buttonPin) \
	uint8_t button_read##buttonHandle (void);

	BUTTON_LIST
#undef BUTTON_DATA


#endif /* BUTTON_H_ */