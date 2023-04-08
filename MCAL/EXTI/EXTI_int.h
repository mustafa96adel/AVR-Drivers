/*
 * EXTI_int.h
 *
 *  Created on: Feb 24, 2023
 *      Author: musta
 */

#ifndef EXTI_EXTI_INT_H_
#define EXTI_EXTI_INT_H_

#define EXTI_INT0							0
#define EXTI_INT1							1
#define EXTI_INT2							2

void M_EXTI_void_enableInt(u8 interruptNumber);
void M_EXTI_void_disableInt(u8 interruptNumber);
void M_EXTI_void_setCallBackFunction(void (*pf)(void) ,u8 interruptNumber);

#endif /* EXTI_EXTI_INT_H_ */
