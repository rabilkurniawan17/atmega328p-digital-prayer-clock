/*
 * eeprom.c
 *
 * Created: 6/9/2026 7:17:54 PM
 *  Author: Admin
 */ 
#include "eeprom.h"

void eeprom_writeByte (uint16_t address, uint8_t data)
{
  while (EECR & (1 << EEPE));

  EEAR = address;
  EEDR = data;

  EECR |= (1 << EEMPE);
  EECR |= (1 << EEPE);
}

uint8_t eeprom_readByte (uint16_t address)
{
  while (EECR & (1 << EEPE));

  EEAR = address;

  EECR |= (1 << EERE);

  return EEDR;
}

void eeprom_writeBlock (PrayerOffset_t *offset, uint16_t startAddress, uint8_t length)
{
  for (int i=startAddress; i<length; i++)
  {
    eeprom_writeByte(i, *(((int8_t*)(offset)) + i));
  }
}

void eeprom_readBlock (PrayerOffset_t *offset, uint16_t startAddress, uint8_t length)
{
  for (int i=startAddress; i<length; i++)
  {
    *(((int8_t*)(offset)) + i) = eeprom_readByte(i);
  }
}