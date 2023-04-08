/*
 * DC_MOTOR_prg.c
 *
 *  Created on: Mar 8, 2023
 *      Author: musta
 */


#include "STD_TYPES.h"
#include "TIMER0_int.h"
#include "Dio_int.h"
#include "DC_MOTOR_cfg.h"
#include "DC_MOTOR_int.h"

void H_DC_MOTOR_voidInit()
{
	timer0_config_t t;
	t.timer_mode = TIMER0_PWM_PHASE_CORRECT_MODE;
	t.oc_mode_configs = TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_CLEAR_MODE;
	M_Timer0_void_Init(&t);
}

void H_DC_MOTOR_voidSetDutyCycle(u8 duty)
{
	M_Timer0_void_setphaseCorrectPWM(DC_MOTOR_FREQUENCY, duty);
}

void H_DC_MOTOR_voidStart(void)
{
//	H_DC_MOTOR_voidInit();
	M_Timer0_void_start();
}

void H_DC_MOTOR_voidStop(void)
{
//	timer0_config_t t;
//	t.timer_mode = TIMER0_PWM_PHASE_CORRECT_MODE;
//	t.oc_mode_configs = TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_NORMAL_MODE;
//	M_Timer0_void_Init(&t);
	M_Timer0_void_setphaseCorrectPWM(DC_MOTOR_FREQUENCY, 0);
//	M_Timer0_void_stop();
}



