/*
 * TIMER0_int.h
 *
 *  Created on: Feb 25, 2023
 *      Author: musta
 */

#ifndef TIMER0_TIMER0_INT_H_
#define TIMER0_TIMER0_INT_H_

#include "STD_TYPES.h"
#include "TIMER0_types.h"

void M_Timer0_void_Init(timer0_config_t* timer0_configs);

void M_Timer0_void_start(void);

void M_Timer0_void_stop(void);

u8 M_Timer_u8_GetCounts(void);

void M_Timer0_void_setDelayTimeMilliSec(u32 delay_value);

void M_Timer0_void_EnableOverFlowInt(void);

void M_Timer0_void_DisableOverFlowInt(void);

void M_Timer0_void_EnabOutCompareleInt(void);

void M_Timer0_void_DisabOutCompareleInt(void);

void M_Timer0_void_setOverFlowCallBack(void(*copy_pf)(void));

void M_Timer0_void_setOutputCompareCallBack(void(*copy_pf)(void));

void M_Timer0_void_setFastPWM(u8 frequency ,u8 duty);

void M_Timer0_void_setphaseCorrectPWM(u8 frequency ,u8 duty);
#endif /* TIMER0_TIMER0_INT_H_ */
