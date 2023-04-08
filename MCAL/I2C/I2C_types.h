/*
 * I2C_types.h
 *
 *  Created on: Mar 11, 2023
 *      Author: musta
 */

#ifndef I2C_I2C_TYPES_H_
#define I2C_I2C_TYPES_H_

typedef enum {
	I2C_MASTER_START_COND_TRANSMITTED = 1,
	I2C_MASTER_REPEATED_START_TRANSMITTED,
	I2C_MASTER_SLA_ADD_WRT_ACK,
	I2C_MASTER_SLA_ADD_WRT_NACK,
	I2C_MASTER_BYTE_TRANSMITTED_ACK,
	I2C_MASTER_BYTE_TRANSMITTED_NACK,
	I2C_MASTER_ARITRATION_LOST,
	I2C_MASTER_SLA_ADD_READ_ACK,
	I2C_MASTER_SLA_ADD_READ_NACK,
	I2C_MASTER_BYTE_RECEIVED_ACK,
	I2C_MASTER_BYTE_RECEIVED_NACK
}I2C_master_status_type;

typedef enum
{
	I2C_NO_DIV,
	I2C_DIV_4,
	I2C_DIV_16,
	I2C_DIV_64
}I2C_prescaler_type;

typedef enum
{
	I2C_GCR_DISALE,
	I2C_GCR_ENALE
}I2C_general_call_recognition_type;


typedef enum
{
	I2C_INT_DISALE,
	I2C_INT_ENALE
}I2C_interrupt_type;

typedef struct
{
	I2C_prescaler_type prescaler;
	I2C_general_call_recognition_type GCR;
	I2C_interrupt_type interrupt;
}I2C_config_type;

#endif /* I2C_I2C_TYPES_H_ */
