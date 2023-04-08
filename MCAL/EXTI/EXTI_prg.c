/*
 * EXTI_prg.c
 *
 *  Created on: Feb 24, 2023
 *      Author: musta
 */
#include "avr/interrupt.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mcu_HW.h"
#include "EXTI_cfg.h"
#include "EXTI_int.h"

static void (*pf[3])(void) = {NULL ,NULL ,NULL};

void M_EXTI_void_enableInt(u8 interruptNumber)
{
	switch(interruptNumber)
	{
	case EXTI_INT0:
		MCUCR_REG &= ~0b00000011;
		MCUCR_REG += ETXI_INT0_INT_CONFIGURATION;
		SET_BIT(GICR,6);
		break;
	case EXTI_INT1:
		MCUCR_REG &= ~0b00001100;
		MCUCR_REG += ETXI_INT1_INT_CONFIGURATION << 2;
		SET_BIT(GICR,7);
		break;
	case EXTI_INT2:
		CLR_BIT(MCUCSR_REG, 6);
		MCUCSR_REG += ETXI_INT2_INT_CONFIGURATION << 6;
		SET_BIT(GICR,5);
		break;
	}
}
void M_EXTI_void_disableInt(u8 interruptNumber)
{
	switch(interruptNumber)
	{
	case EXTI_INT0:
		CLR_BIT(GICR,6);
		break;
	case EXTI_INT1:
		CLR_BIT(GICR,7);
		break;
	case EXTI_INT2:
		CLR_BIT(GICR,5);
		break;
	}
}

void M_EXTI_void_setCallBackFunction(void (*copy_pf)(void) ,u8 interruptNumber)
{
	pf[interruptNumber] = copy_pf;
}

ISR(INT0_vect)
{
	SET_BIT(GIFR, 6);
	if (pf[0])
		pf[0]();
}

ISR(INT1_vect)
{
	SET_BIT(GIFR, 7);
	if (pf[1])
		pf[1]();
}

ISR(INT2_vect)
{
	SET_BIT(GIFR, 5);
	if (pf[2])
		pf[2]();
}
