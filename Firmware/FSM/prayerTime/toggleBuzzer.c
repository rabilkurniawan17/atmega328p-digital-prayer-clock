/*
 * toggleBuzzer.c
 *
 * Created: 5/28/2026 8:22:05 PM
 *  Author: Admin
 */ 
#include "toggleBuzzer.h"
#include "../../Drivers/timer0.h"
#include "../../Config/pin_config.h"

static Buzzer_t buzzer;

void buzzerStart(void)
{
  buzzer.active     = true;
  buzzer.counter      = 0;
  buzzer.previousMillis = millis();
  buzzer.state      = false;
}

void buzzerUpdate(uint32_t interval, uint8_t counter)
{
  if (!buzzer.active)
    return;

  if (millis() - buzzer.previousMillis >= interval)
  {
    buzzer.previousMillis = millis();
    buzzer.state      = !buzzer.state;
    buzzer.counter++;

    if (buzzer.state)
    {
      BUZZER_PORT |= (1<<BUZZER_PIN);
    }   
    else
    {
      BUZZER_PORT &= ~(1<<BUZZER_PIN);
    }   

    if (buzzer.counter >= counter)
    {
      buzzer.active = false;
      BUZZER_PORT &= ~(1<<BUZZER_PIN);
    }
  }
}