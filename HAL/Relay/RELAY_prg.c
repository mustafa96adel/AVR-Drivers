/*
 * RELAY_prg.c
 *
 *  Created on: Mar 4, 2023
 *      Author: musta
 */

#include "Dio_int.h"
#include "RELAY_cfg.h"
#include "RELAY_types.h"
#include "RELAY_int.h"
void H_RELAY_void_open(RELAY_NUMBER_type rel)
{
	switch(rel)
	{
	case RELAY_1:
		M_Dio_void_setPinValue(RELAY_1_PIN, DIO_HIGH);
		break;
	case RELAY_2:
		M_Dio_void_setPinValue(RELAY_2_PIN, DIO_HIGH);
		break;
	}
}

void H_RELAY_void_close(RELAY_NUMBER_type rel)
{
	switch(rel)
	{
	case RELAY_1:
		M_Dio_void_setPinValue(RELAY_1_PIN, DIO_LOW);
		break;
	case RELAY_2:
		M_Dio_void_setPinValue(RELAY_2_PIN, DIO_LOW);
		break;
	}
}
