/*
 * twi.h
 *
 * Created: 5/13/2026 1:24:18 PM
 *  Author: Admin
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <stdint.h>

#define PRESCALLER_MASK		0xF8

#define START_OK			0x08 //START condition has been transmitted.
#define REPEATED_START_OK	0x10 //Repeated START condition has been transmitted.
#define SLAVE_W_ACK			0x18 //SLA+W has been transmitted; ACK has been received.
#define DATA_TX_ACK			0x28 //Data byte has been transmitted; ACK has been received.
#define DATA_TX_NACK        0x30

#define SLAVE_R_ACK			0x40 //SLA+R has been transmitted; NACK has been received.
#define SLAVE_R_NACK        0x48
#define DATA_RX_ACK			0x50 //Data byte received; ACK has been returned.
#define DATA_RX_NACK		0x58 //Data byte received; NACK has been returned.

#define F_CPU 16000000UL

typedef enum
{
	twi_Status_ok = 0,
	twi_Status_startFailed,
	twi_Status_repeatedStartFailed,
	twi_Status_slaveWAckFailed,
	twi_Status_RAckFailed,
	twi_Status_dataTxFailed,
	twi_Status_dataRxFailed
}twi_Status_e;

void		 twi_init			(uint32_t sclFreq);
void		 twi_stop			(void);
twi_Status_e twi_start			(void);
twi_Status_e twi_repeatedStart	(void);
twi_Status_e twi_writeAddress	(uint8_t  address);
twi_Status_e twi_writeByte		(uint8_t  data);
twi_Status_e twi_readByteAck	(uint8_t  *data);
twi_Status_e twi_readByteNack	(uint8_t  *data);


#endif /* TWI_H_ */