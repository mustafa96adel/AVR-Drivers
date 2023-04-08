/*
 * ADC_prg.c
 *
 *  Created on: Mar 3, 2023
 *      Author: musta
 */
#include "avr/interrupt.h"
#include "Mcu_HW.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "ADC_priv.h"
#include "ADC_types.h"
#include "ADC_int.h"

static void (*pf)(void) = NULL;
void M_ADC_Init(const ADC_config_type* copy_config)
{
	SET_BIT(ADCSRA, 7);
	ADMUX = 0;
	ADMUX = (copy_config->ref << 6) + (copy_config->adjust << 5);
	WRITE_BIT(ADCSRA, 5, copy_config->trigger);
	PUT_N_BITS(SFIOR, 3, 5, copy_config->auto_trig_source);
	PUT_N_BITS(ADCSRA, 3, 0, copy_config->prescaler);
}
u16 M_ADC_getDigitalValueSynchNonBlocking(ADC_channel_id_type id)
{
	PUT_N_BITS(ADMUX, 5, 0, id);
	u16 counter = 0;
	M_ADC_void_start();
	while(GET_BIT(ADCSRA, 4) == 1 && counter < 50000)
		counter++;
	if(counter < 50000)
	{
		SET_BIT(ADCSRA, 4);
		return M_ADC_u16_read();
	}
	return 0;
}
void M_ADC_voidSetChannel(u8 channelNumer)
{
	PUT_N_BITS(ADMUX, 5, 0, channelNumer);
}

void M_ADC_void_start(void)
{
	SET_BIT(ADCSRA, 6);
}
void M_ADC_void_stop(void)
{
	CLR_BIT(ADCSRA, 7);
}
void M_ADC_void_enable_interrupt(void)
{
	SET_BIT(ADCSRA, 3);
}
void M_ADC_void_disable_interrupt(void)
{
	CLR_BIT(ADCSRA, 3);
}
u16 M_ADC_u16_read(void)
{
	if(GET_BIT(ADMUX, 5))
	{
		return ADCH;
	}
	u16 adcValue = ADCL;
	return ADCH + adcValue;
}

void M_ADC_void_getDigitalValueAsynchCallBack(void(*action)(void), ADC_channel_id_type id)
{
	PUT_N_BITS(ADMUX, 5, 0, id);
	M_ADC_void_start();
	pf = action;
}

void M_ADC_void_setCallBackFunction(void(*action)(void))
{
	pf = action;
}

ISR(ADC_vect)
{
	if(pf)
		pf();
}
