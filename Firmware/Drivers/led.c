/*
 * led.c
 *
 * Created: 5/14/2026 9:36:42 PM
 *  Author: Admin
 */ 
//==============toggle pin LED every 500 ms==================

#include <avr/interrupt.h>
#include <avr/io.h>
#include "led.h"
#include "../Config/pin_config.h"

void led_init(void)
{
  //CTC Mode
  TCCR2A = (1<<WGM21);

  //set prescaler: 1024
  TCCR2B = (7 << CS20);

  //set OCR2A value: 250 (interrupt every 16ms)
  OCR2A = 250;

  //set Output Compare match interrupt enable
  TIMSK2 = (1<<OCIE2A);

  TCNT2 = 0;

  sei();
}

ISR(TIMER2_COMPA_vect)
{
  static volatile uint8_t counter;
  counter++;
  if(counter == 31)
  {   
    LED_PORT ^= (1<<LED_PIN);
    counter = 0;
  }
}