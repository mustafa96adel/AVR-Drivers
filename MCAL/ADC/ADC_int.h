/*
 * ADC_int.h
 *
 *  Created on: Mar 3, 2023
 *      Author: musta
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_
#include "STD_TYPES.h"
#include "ADC_types.h"

void M_ADC_Init(const ADC_config_type* copy_config);
u16 M_ADC_getDigitalValueSynchNonBlocking(ADC_channel_id_type id);
void M_ADC_voidSetChannel(u8 channelNumer);
void M_ADC_void_start(void);
void M_ADC_void_stop(void);
void M_ADC_void_enable_interrupt(void);
void M_ADC_void_disable_interrupt(void);
u16 M_ADC_u16_read(void);
void M_ADC_void_getDigitalValueAsynchCallBack(void(*action)(void), ADC_channel_id_type id);
void M_ADC_void_setCallBackFunction(void(*action)(void));

#endif /* MCAL_ADC_ADC_INT_H_ */
