/*
 * I2C_prg.c
 *
 *  Created on: Mar 11, 2023
 *      Author: musta
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mcu_HW.h"
#include "I2C_cfg.h"
#include "I2C_types.h"
#include "I2C_priv.h"
#include "I2C_int.h"

void M_I2C_voidInit(I2C_config_type* configs)
{
	TWCR = 0;
	TWCR += configs->interrupt;
	PUT_N_BITS(TWSR, 2, 0, configs->prescaler);
	WRITE_BIT(TWAR, 0, configs->GCR);
	//TWBR = 0x0C;		//400KHz .......... edited from 0xC0 to 0x0C
	TWBR = 72;
	SET_BIT(TWCR, 7);
}

void M_I2C_voidSetBaudeRate(u16 rate)
{
	TWBR = (((I2C_MAIN_CLOCK_FREQ_IN_MEGA_HZ * 1000000) / rate) - 16) / TWO_TO_THE_POWER(1 + 2 *(GET_N_BITS(TWSR, 2, 0)));
}
void M_I2C_voidSendStart(void)
{
	TWCR = I2C_START;
	while(GET_BIT(TWCR, 7) == 0);
}
void M_I2C_voidSendStop(void)
{
	TWCR = I2C_STOP;
}

void M_I2C_voidSendByte(u8 data)
{
	TWDR = data;
	TWCR = I2C_SEND;
	while(GET_BIT(TWCR, 7) == 0);
}

u8 M_I2C_u8ReceiveByteACK(void)
{
	SET_BIT(TWCR, 7);
	TWCR = I2C_RECEIVE_ACK;
	while(GET_BIT(TWCR, 7) == 0);
	return TWDR;
}

u8 M_I2C_u8ReceiveByteNACK(void)
{
	SET_BIT(TWCR, 7);
	TWCR = I2C_RECEIVE_NACK;
	while(GET_BIT(TWCR, 7) == 0);
	return TWDR;
}
I2C_master_status_type M_I2C_u8GetStatus(void)
{
	return GET_N_BITS(TWSR, 5, 3);
}
