/*
 * hc595shift.c
 *
 * Created: 5/14/2026 10:12:10 PM
 *  Author: Admin
 */ 

#include "hc595shift.h"

void hc595shift_shiftData(
	volatile uint8_t *dataPort,
    uint8_t           dataPin,
    volatile uint8_t *clockPort,
    uint8_t           clockPin,
    uint8_t           data
)
{ 
  for (int i=0; i<8; i++)
  {
    if (data & 0x80)
    {
      *dataPort |= (1<< dataPin);
    }
    else
    {
      *dataPort &= ~(1 << dataPin);
    }

    *clockPort &= ~(1<< clockPin);
    *clockPort |= (1 << clockPin);

    data <<= 1;
  }
}