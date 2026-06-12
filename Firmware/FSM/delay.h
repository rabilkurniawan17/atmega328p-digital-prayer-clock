/*
 * delay.h
 *
 * Created: 5/26/2026 12:54:22 PM
 *  Author: Admin
 */ 


#ifndef DELAY_H_
#define DELAY_H_

#include <stdbool.h>
#include <stdint.h>

void delay_toggleUpdate   (uint32_t toggleTime);
bool delay_isDelayFinish (void);



#endif /* DELAY_H_ */