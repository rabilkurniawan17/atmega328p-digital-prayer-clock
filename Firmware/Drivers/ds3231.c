/*
 * ds3231.c
 *
 * Created: 5/13/2026 2:30:58 PM
 *  Author: Admin
 */ 

#include "ds3231.h"
#include "../Drivers/twi.h"

//============helper function===========

static uint16_t year2To4Converter(uint8_t year)
{
  return (year + 2000);
}

static uint8_t year4To2Converter(uint16_t year)
{
  return (year % 100);
}

static uint8_t bcdToDecimal(uint8_t value) // 0x45 -> 45
{ 
  return (((value >> 4 ) * 10) + (value & 0x0F)); 
}

static uint8_t decimalToBcd(uint8_t value)
{
  return (((value/10) << 4) | (value % 10));
}

static uint8_t ds3231_writeRegister(uint8_t reg, uint8_t data)
{
  //TWI start
  if (twi_start() != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
  //TWI send addres << 1 + 0 : for write
  if (twi_writeAddress((DS3231_ADDRESS << 1) | 0) != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
  //TWI send register (second ~ year)
  if (twi_writeByte(reg) != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
  //TWI send data
  if (twi_writeByte(data) != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
  //finish
  twi_stop();
  return 1;
}

static uint8_t ds3231_readRegister(uint8_t reg, uint8_t *data)
{
  //TWI start
  if (twi_start() != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
  //TWI send addres << 1 + 0 : for write register that want to read (second ~ year)
  if (twi_writeAddress((DS3231_ADDRESS << 1) | 0) != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
  //TWI send register (second ~ year)
  if (twi_writeByte(reg) != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
//======================================================================================
  //repeated start
  if (twi_repeatedStart() != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
  //TWI send addres << 1 + 1 : for read data
  if (twi_writeAddress((DS3231_ADDRESS << 1) | 1) != twi_Status_ok)
  {
    twi_stop();
    return 0;
  }
  //read with NACK because this the last data that we want
  if (twi_readByteNack(data) != twi_Status_ok)
  {
    twi_stop();
    return 0;
  } 
  twi_stop();
  return 1;
}

void ds3231_getTime(ds3231_Time_t *time)
{
  uint8_t buffer; 
  
#define TIME_DATA(timeName, regName) \
  ds3231_readRegister(DS3231_##regName, &buffer); \
  time->timeName = bcdToDecimal(buffer);
  
  TIME_LIST
#undef TIME_DATA
  
  ds3231_readRegister(DS3231_YEAR, &buffer);
  time->year = year2To4Converter(bcdToDecimal(buffer));
}

void ds3231_setTime(ds3231_Time_t *time){

#define TIME_DATA(timeName, regName) \
  ds3231_writeRegister(DS3231_##regName, decimalToBcd(time->timeName));
  
  TIME_LIST
  
#undef TIME_DATA

  ds3231_writeRegister(DS3231_YEAR, decimalToBcd(year4To2Converter(time->year)));
}