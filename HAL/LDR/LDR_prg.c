/*
 * LDR_prg.c
 *
 *  Created on: Mar 12, 2023
 *      Author: musta
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_types.h"
#include "ADC_int.h"
#include "LDR_int.h"

extern const ADC_config_type ADC_conf_LDR;

void H_LDR_voidInit(void)
{
	M_ADC_Init(&ADC_conf_LDR);
}

u8 H_LDR_u8GetLighteningValue(void)
{
	s16 value = M_ADC_getDigitalValueSynchNonBlocking(ADC_conf_LDR.id);
//	M_ADC_voidSetChannel(1);
	return value;
}
