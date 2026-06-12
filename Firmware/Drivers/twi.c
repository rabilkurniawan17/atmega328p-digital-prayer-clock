/*
 * twi.c
 *
 * Created: 5/13/2026 1:29:25 PM
 *  Author: Admin
 */ 

#include "twi.h"
#include "../Display/uart.h"

static uint8_t getStatus(void)
{
  return (TWSR & PRESCALLER_MASK);
}

void twi_init(uint32_t sclFreq)
{
  //set prescaller
  TWSR = 0; //prescaler = 1

  //set bit rate
  TWBR = ((F_CPU/sclFreq) - 16) / 2;

  //turn on TWI
  TWCR = (1<<TWEN); 
}

twi_Status_e twi_start(void)
{
  //set TWINT, TWSTA, TWEN
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

  //wait until twi peripheral finish the job
  while(!(TWCR & (1<<TWINT)));

  uint8_t status = getStatus();
  if(status != START_OK && status != REPEATED_START_OK)
  {
    return twi_Status_startFailed;
  }
  return twi_Status_ok;
}

twi_Status_e twi_repeatedStart(void)
{
  //set TWINT, TWSTA, TWEN
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

  //wait until twi peripheral finish the job
  while(!(TWCR & (1<<TWINT)));

  uint8_t status = getStatus();
  if(status != START_OK && status != REPEATED_START_OK)
  {
    return twi_Status_repeatedStartFailed;
  }
  return twi_Status_ok;
}

void twi_stop(void)
{
  //set TWINT, TWSTO, TWEN
  TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
  while(TWCR & (1<<TWSTO));
}
twi_Status_e twi_writeAddress(uint8_t address)
{
  //put data into TWDR
  TWDR = address;

  //set TWINT and TWEN
  TWCR = (1<<TWINT) | (1<<TWEN);

  //wait until its finish
  while(!(TWCR & (1<<TWINT)));

  uint8_t status = getStatus();

  //cek for write or read from slave
  if((address & 0x1) == 0)
  { //if write
    if(status != SLAVE_W_ACK)
      return twi_Status_slaveWAckFailed;
  }
  else
  {
    if(status != SLAVE_R_ACK)
      return twi_Status_RAckFailed;
  }
  return twi_Status_ok;
}

twi_Status_e twi_writeByte(uint8_t data)
{
  //put data into TWDR
  TWDR = data;

  //set TWINT and TWEN
  TWCR = (1<<TWINT) | (1<<TWEN);

  //wait until its finish
  while(!(TWCR & (1<<TWINT)));

  uint8_t status = getStatus();

  if(status != DATA_TX_ACK)
  {
    return twi_Status_dataTxFailed;
  }
  return twi_Status_ok;
}

twi_Status_e twi_readByteAck(uint8_t *data)
{
  //set TWINT, TWEN, TWEA
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

  //wait until its finish
  while(!(TWCR & (1<<TWINT)));

  uint8_t status = getStatus();
  if(status != DATA_RX_ACK)
  {
    return twi_Status_dataRxFailed;
  }

  //put data from TWDR into data buffer
  *data = TWDR;
  return twi_Status_ok;
}

twi_Status_e twi_readByteNack(uint8_t *data)
{
  //set TWINT, TWEN
  TWCR = (1<<TWINT) | (1<<TWEN);

  //wait until its finish
  while(!(TWCR & (1<<TWINT)));

  uint8_t status = getStatus();
  if(status != DATA_RX_NACK)
  {
    return twi_Status_dataRxFailed;
  }

  //put data from TWDR into data buffer
  *data = TWDR;
  return twi_Status_ok;
}