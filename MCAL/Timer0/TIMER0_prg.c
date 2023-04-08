/*
 * TIMER0_prg.c
 *
 *  Created on: Feb 25, 2023
 *      Author: musta
 */
#include "Mcu_HW.h"
#include "avr/delay.h"
#include "avr/interrupt.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER0_int.h"
#include "TIMER0_cfg.h"

static timer0_config_t timer0_configs;
static u8 remainder;
static u32 number_of_overflows = 0;
static u32 current_number_of_overflows = 0;
static void (*pf_ovf)(void);
static void (*pf_oc)(void);
static u16 prescaler[5] = {1, 8, 64, 256, 1024};

static u8 getIndexOfClosestPrescaler(u16 value)
{
	if (value > prescaler[4]) return 4;
	for (u8 i = 0; i < 5; i++)
	{
		if (value < prescaler[i])
		{
			if (value - prescaler[i - 1] < prescaler[i] - value)
				return i - 1;
			else
				return i;
		}
	}
	return 5;
}
void M_Timer0_void_Init(timer0_config_t* copy_timer0_configs)
{
	timer0_configs = *copy_timer0_configs;
	CLR_N_BITS(TCCR0, 4, 3);
	TCCR0 += (timer0_configs.oc_mode_configs << 4) +
			 (timer0_configs.timer_mode << 3);
	OCR0 = timer0_configs.value_of_OCR0;
}

void M_Timer0_void_start(void)
{
	CLR_N_BITS(TCCR0, 3, 0);
	TCCR0 += timer0_configs.prescaler;
}

void M_Timer0_void_stop(void)
{
	CLR_N_BITS(TCCR0, 3, 0);
}

u8 M_u8_Timer_GetCounts(void)
{
	return TCNT0;
}

void M_Timer0_void_EnablOverFloweInt(void)
{
		SET_BIT(TIMSK, 0);
}

void M_Timer0_void_DisableOverFlowInt(void)
{
		CLR_BIT(TIMSK, 0);
}

void M_Timer0_void_EnabOutCompareleInt(void)
{
	SET_BIT(TIMSK, 1);
}

void M_Timer0_void_DisabOutCompareleInt(void)
{
	CLR_BIT(TIMSK, 1);
}

void M_Timer0_void_setDelayTimeMilliSec(u32 delay_value)
{
	u32 num_of_ticks = (TIMER0_F_CPU_IN_MEGA_HZ * delay_value * 1000) / prescaler[timer0_configs.prescaler - 1];
	switch(timer0_configs.timer_mode)
	{
	case TIMER0_NORMAL_MODE:
		number_of_overflows = num_of_ticks >> 8;
		remainder = num_of_ticks & 0xff;
		if (remainder != 0)
		{
			number_of_overflows++;
			TCNT0 = 256 - remainder;
		}
		break;
	case TIMER0_CTC_MODE:
		number_of_overflows = num_of_ticks / timer0_configs.value_of_OCR0;
		remainder = num_of_ticks % timer0_configs.value_of_OCR0;
		if (remainder != 0)
		{
			number_of_overflows++;
			TCNT0 = 256 - remainder;
		}
		break;
	default :
		/* do nothing */
		break;
	}
	//M_Timer0_void_start();

}

void M_Timer0_void_setOutputCompareCallBack(void(*copy_pf)(void))
{
		pf_oc = copy_pf;
}

M_Timer0_void_setOverFlowCallBack(void(*copy_pf)(void))
{
	pf_ovf = copy_pf;
}

void M_Timer0_void_setFastPWM(u8 frequency ,u8 duty)
{
	u8 prescaler_index = getIndexOfClosestPrescaler((TIMER0_F_CPU_IN_MEGA_HZ*1000000)/(frequency * 256));
	timer0_configs.prescaler = prescaler_index + 1;
	switch(timer0_configs.oc_mode_configs)
	{
	case TIMER0_COMPARE_OUTPUT_FAST_PWM_CLEAR_MODE :
		OCR0 = (256 * duty) / 100 - 1;
		break;
	case TIMER0_COMPARE_OUTPUT_FAST_PWM_SET_MODE :
		OCR0 = 255 - (256 * duty) / 100;
		break;
	default :
		/* error */
		break;
	}
}

void M_Timer0_void_setphaseCorrectPWM(u8 frequency ,u8 duty)
{
	u8 prescaler_index = getIndexOfClosestPrescaler((TIMER0_F_CPU_IN_MEGA_HZ*1000000)/(frequency * 510));
	timer0_configs.prescaler = prescaler_index + 1;
	switch(timer0_configs.oc_mode_configs)
	{
	case TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_CLEAR_MODE :
		OCR0 = (255 * duty) / 100;
		break;
	case TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_SET_MODE :
		OCR0 = 255 - (255 * duty) / 100;
		break;
	default :
		/* error */
		break;
	}

}

ISR(TIMER0_OVF_vect)
{
	current_number_of_overflows++;
	if (current_number_of_overflows == number_of_overflows)
	{
		if(pf_ovf)
			pf_ovf();
		current_number_of_overflows = 0;
		TCNT0 = 256 - remainder;
	}
}

ISR(TIMER0_COMP_vect)
{
	if(pf_oc)
		pf_oc();
}
