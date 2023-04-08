/*
 * I2C_int.h
 *
 *  Created on: Mar 11, 2023
 *      Author: musta
 */

#ifndef I2C_I2C_INT_H_
#define I2C_I2C_INT_H_

#include "I2C_types.h"

#define M_I2C_ADDRESS_WRITE(ADDRESS)				(ADDRESS << 1)
#define M_I2C_ADDRESS_READ(ADDRESS)				((ADDRESS << 1) + 1)
void M_I2C_voidInit(I2C_config_type* configs);
void M_I2C_voidSendStart(void);
void M_I2C_voidSendStop(void);
void M_I2C_voidSendByte(u8);
u8 M_I2C_u8ReceiveByteACK(void);
u8 M_I2C_u8ReceiveByteNACK(void);
I2C_master_status_type M_I2C_u8GetStatus(void);

#endif /* I2C_I2C_INT_H_ */
