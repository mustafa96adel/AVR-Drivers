/*
 * SSD_prg.c
 *
 *  Created on: Feb 17, 2023
 *      Author: aya_enan
 */
#include <avr/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Dio_int.h"

#include "SSD_priv.h"
#include "SSD_types.h"
#include "SSD_cfg.h"
#include "SSD_int.h"


void H_void_displayIntNumber(u16 number)
{
	u8 arr[4] = { number % 10, (number / 10) % 10,(number / 100)  % 10, number / 1000};
	for(int i = 0; i < SSD_DISPLAY_TIME; i++)
	{
		M_Dio_void_setPinValue(SSD_A_PIN, GET_BIT(arr[0],0));
		M_Dio_void_setPinValue(SSD_B_PIN, GET_BIT(arr[0],1));
		M_Dio_void_setPinValue(SSD_C_PIN, GET_BIT(arr[0],2));
		M_Dio_void_setPinValue(SSD_D_PIN, GET_BIT(arr[0],3));

		M_Dio_void_setPinValue(SSD_DIG1_EN, DIO_LOW);
		_delay_ms(1);
		M_Dio_void_setPinValue(SSD_DIG1_EN, DIO_HIGH);

		M_Dio_void_setPinValue(SSD_A_PIN, GET_BIT(arr[1],0));
		M_Dio_void_setPinValue(SSD_B_PIN, GET_BIT(arr[1],1));
		M_Dio_void_setPinValue(SSD_C_PIN, GET_BIT(arr[1],2));
		M_Dio_void_setPinValue(SSD_D_PIN, GET_BIT(arr[1],3));

		M_Dio_void_setPinValue(SSD_DIG2_EN, DIO_LOW);
		_delay_ms(1);
		M_Dio_void_setPinValue(SSD_DIG2_EN, DIO_HIGH);


		M_Dio_void_setPinValue(SSD_A_PIN, GET_BIT(arr[2],0));
		M_Dio_void_setPinValue(SSD_B_PIN, GET_BIT(arr[2],1));
		M_Dio_void_setPinValue(SSD_C_PIN, GET_BIT(arr[2],2));
		M_Dio_void_setPinValue(SSD_D_PIN, GET_BIT(arr[2],3));

		M_Dio_void_setPinValue(SSD_DIG3_EN, DIO_LOW);
		_delay_ms(1);
		M_Dio_void_setPinValue(SSD_DIG3_EN, DIO_HIGH);


		M_Dio_void_setPinValue(SSD_A_PIN, GET_BIT(arr[3],0));
		M_Dio_void_setPinValue(SSD_B_PIN, GET_BIT(arr[3],1));
		M_Dio_void_setPinValue(SSD_C_PIN, GET_BIT(arr[3],2));
		M_Dio_void_setPinValue(SSD_D_PIN, GET_BIT(arr[3],3));

		M_Dio_void_setPinValue(SSD_DIG4_EN, DIO_LOW);
		_delay_ms(1);
		M_Dio_void_setPinValue(SSD_DIG4_EN, DIO_HIGH);
	}
	return;

}


