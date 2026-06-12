/*
 * gpio.c
 *
 * Created: 5/14/2026 7:06:11 AM
 *  Author: Admin
 */ 

#include "gpio.h"
#include "../Config/pin_config.h"


void gpio_init(void)
{
  //============set CLOCK, DATE and SCHEDULE pin as OUTPUT============

  //CLOCK
  CLOCK_LATCH_DDR   |= (1<<CLOCK_LATCH_PIN);
  CLOCK_DATA_DDR    |= (1<<CLOCK_DATA_PIN);
  CLOCK_CLK_DDR   |= (1<<CLOCK_CLK_PIN);

  //DATE
  DATE_LATCH_DDR    |= (1<<DATE_LATCH_PIN);
  DATE_DATA_DDR   |= (1<<DATE_DATA_PIN);
  DATE_CLK_DDR    |= (1<<DATE_CLK_PIN);

  //SCHEDULE
  SCHEDULE_LATCH_DDR  |= (1<<SCHEDULE_LATCH_PIN);
  SCHEDULE_DATA_DDR |= (1<<SCHEDULE_DATA_PIN);
  SCHEDULE_CLK_DDR  |= (1<<SCHEDULE_CLK_PIN);

  //=================SET BUZZER AND LED as OUTPUT=======================
  LED_DDR       |= (1<<LED_PIN);
  BUZZER_DDR      |= (1<<BUZZER_PIN);

  //====================SET ALL BUTTON as INPUT PULLUP==================
  BUTTON_SET_DDR    &= ~(1<<BUTTON_SET_PIN);
  BUTTON_SET_PORT   |= (1<<BUTTON_SET_PIN);

  BUTTON_DOWN_DDR   &= ~(1<<BUTTON_DOWN_PIN);
  BUTTON_DOWN_PORT  |= (1<<BUTTON_DOWN_PIN);

  BUTTON_UP_DDR   &= ~(1<<BUTTON_UP_PIN);
  BUTTON_UP_PORT    |= (1<<BUTTON_UP_PIN);

  BUTTON_OFFSET_DDR &= ~(1<<BUTTON_OFFSET_PIN);
  BUTTON_OFFSET_PORT  |= (1<<BUTTON_OFFSET_PIN);
}