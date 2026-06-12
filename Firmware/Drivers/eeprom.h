/*
 * eeprom.h
 *
 * Created: 6/9/2026 7:17:43 PM
 *  Author: Admin
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include <stdint.h>
#include "../FSM/offset.h"

void    eeprom_writeByte (uint16_t address, uint8_t data);
uint8_t eeprom_readByte  (uint16_t address);

void eeprom_writeBlock (PrayerOffset_t *offset, uint16_t startAddress, uint8_t length);
void eeprom_readBlock  (PrayerOffset_t *offset, uint16_t startAddress, uint8_t length);


#endif /* EEPROM_H_ */