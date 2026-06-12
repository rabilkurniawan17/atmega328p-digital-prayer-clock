/*
 * hc595shift.h
 *
 * Created: 5/14/2026 10:11:50 PM
 *  Author: Admin
 */ 


#ifndef HC595SHIFT_H_
#define HC595SHIFT_H_

#include <stdint.h>

void hc595shift_shiftData(volatile uint8_t *dataPort, 
					 	  uint8_t           dataPin, 
						  volatile uint8_t *clockPort, 
						  uint8_t           clockPin, 
						  uint8_t           data);


#endif /* HC595SHIFT_H_ */