/*
 * EEPROM_prg.c
 *
 *  Created on: Mar 11, 2023
 *      Author: musta
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_int.h"
#include "EEPROM_int.h"

extern I2C_config_type I2C_config;
void H_EEPROM_voidInit(void)
{
	M_I2C_voidInit(&I2C_config);
}

void H_EEPROM_voidWriteByte(u16 address, u8 data)
{
	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_START_COND_TRANSMITTED);
	M_I2C_voidSendByte(0xA0 + ((GET_N_BITS(address, 2, 8)) << 1));
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_WRT_ACK);
	M_I2C_voidSendByte(address);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);
	M_I2C_voidSendByte(data);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);
	M_I2C_voidSendStop();
}

u8 H_EEPROM_u8ReadByte(u16 address)
{
	u8 value;
	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_START_COND_TRANSMITTED);
	M_I2C_voidSendByte(0xA0 + M_I2C_ADDRESS_WRITE(GET_N_BITS(address, 2, 8)));
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_WRT_ACK);
	M_I2C_voidSendByte(address);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);
	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_REPEATED_START_TRANSMITTED);
	M_I2C_voidSendByte(0xA0 + M_I2C_ADDRESS_READ(0));
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_READ_ACK);
	value = M_I2C_u8ReceiveByteNACK();
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_RECEIVED_NACK);
	M_I2C_voidSendStop();
	return value;
}
