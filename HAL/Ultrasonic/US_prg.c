/*
 * US_prg.c
 *
 *  Created on: Mar 2, 2023
 *      Author: musta
 */

#include <avr/delay.h>
#include "STD_TYPES.h"
#include "Dio_int.h"
#include "Port_types.h"
#include "Port_int.h"
#include "TIMER1_int.h"
#include "US_cfg.h"
#include "US_int.h"

static Port_ConfigType trig_stop = { US_TR_PIN, PORT_PIN_LEVEL_LOW, PORT_PINDIR_INPUT, PORT_PIN_IN_ATTATCH_FLOATING};
static Port_ConfigType power_stop = { US_POWER_PIN, PORT_PIN_LEVEL_LOW, PORT_PINDIR_INPUT, PORT_PIN_IN_ATTATCH_FLOATING};
static Port_ConfigType GND_stop = { US_GND_PIN, PORT_PIN_LEVEL_LOW, PORT_PINDIR_INPUT, PORT_PIN_IN_ATTATCH_FLOATING};
static volatile u8 count = 0;
static volatile u16 time1, time2 = 5000;
static void action(void)
{
	count++;
	if (count == 1)
	{
		M_TIMER1_InputCaptureEdge(ICU_FALLING);
		time1 = M_TIMER1_ICR_Read();
	}
	else
	{
		time2 = M_TIMER1_ICR_Read();
	}
}
void H_US_void_Init(void)
{
	M_TIMER1_SetCallBack(TIMER1_ICU_INTERRUPT, action);
	M_TIMER1_Init(TIMER1_NORMAL_MODE, TIMER1_PRESCALER_1024);
}

u16 H_US_u16_Get_Distance(void)
{
	M_TIMER1_InputCaptureEdge(ICU_RISING);
	M_TIMER1_ICU_InterruptEnable();
	M_Dio_void_setPinValue(US_TR_PIN, DIO_HIGH);
	_delay_ms(50);
	M_Dio_void_setPinValue(US_TR_PIN, DIO_LOW);
	while(count < 2);
	count = 0;
	M_TIMER1_ICU_InterruptDisable();
	return time2 - time1;
}

void H_US_void_stop(void)
{
	M_TIMER1_Init(TIMER1_NORMAL_MODE, TIMER1_STOP);
	Port_Init(&power_stop, 1);
	Port_Init(&trig_stop, 1);
	Port_Init(&GND_stop, 1);
}
