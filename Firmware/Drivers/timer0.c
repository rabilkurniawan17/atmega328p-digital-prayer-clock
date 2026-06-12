/*
 * timer0.c
 *
 * Created: 5/19/2026 9:22:49 PM
 *  Author: Admin
 */ 

#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>


static volatile uint32_t gCounter = 0;

void timer0_init(void){
  //set ctc mode
  TCCR0A = (1<<WGM01);

  //set prescaller clk/64
  TCCR0B = (1<<CS01) | (1<<CS00);

  //clear TCNT0
  TCNT0 = 0;

  //set OCR0A value for 1ms interrupt
  OCR0A = 249;

  //enable Interrupt when compare match
  TIMSK0 = (1<<OCIE0A);

  //enable general interrupt
  sei();
}

uint32_t millis(void){
  uint32_t temp;

  cli();
  temp = gCounter;
  sei();

  return temp;
}

ISR(TIMER0_COMPA_vect){
  gCounter++;
}