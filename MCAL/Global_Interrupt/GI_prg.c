/*
 * GI_prg.c
 *
 *  Created on: Feb 24, 2023
 *      Author: musta
 */

#include "BIT_MATH.h"
#include "Mcu_HW.h"
void M_GI_disable(void);
#include "GI_int.h"

void M_GI_enable(void)
{
	SET_BIT(SREG, 7);
}
void M_GI_disable(void)
{
	CLR_BIT(SREG, 7);
}
