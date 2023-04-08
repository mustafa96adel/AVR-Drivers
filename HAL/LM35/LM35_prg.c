/*
 * LM35_prg.c
 *
 *  Created on: Mar 8, 2023
 *      Author: musta
 */
#include "STD_TYPES.h"
#include "ADC_int.h"

extern const ADC_config_type ADC_conf_LM35;
void H_LM35_void_init(void)
{
	M_ADC_Init(&ADC_conf_LM35);
}

s16 H_LM35_s16_getTemp(void)
{
	s16 temp = M_ADC_getDigitalValueSynchNonBlocking(ADC_conf_LM35.id);
//	M_ADC_voidSetChannel(0);
	if ((temp * 500) % 256 > 128)
	{
		temp = temp * 500 / 256 + 1;
	}
	else
		temp = temp * 500 / 256;

	return temp;
}
