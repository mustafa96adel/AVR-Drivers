/*
 * DC_MOTOR_int.h
 *
 *  Created on: Mar 8, 2023
 *      Author: musta
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_INT_H_
#define HAL_DC_MOTOR_DC_MOTOR_INT_H_

void H_DC_MOTOR_voidInit();

void H_DC_MOTOR_voidSetDutyCycle(u8 duty);

void H_DC_MOTOR_voidStart(void);

void H_DC_MOTOR_voidStop(void);

#endif /* HAL_DC_MOTOR_DC_MOTOR_INT_H_ */
