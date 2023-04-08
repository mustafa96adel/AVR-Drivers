/*
 * KP_prg.c
 *
 *  Created on: Feb 23, 2023
 *      Author: musta
 */
#include <avr/delay.h>
#include "STD_TYPES.h"
#include "Dio_int.h"
#include "KP_cfg.h"
#include "KP_int.h"

extern u8 KP_rows[4];
extern u8 KP_columns[4];
#if KP_USE_AS == KP_CALCULATOR
extern s8 KP_keys[4][4];

#elif KP_USE_AS == KP_NUMBERS
extern u8 KP_keys[4][4];

#else
#error("wrong configurations");
#endif

u8 H_KP_u8_getPressedKey(void)
{
	u8 j = 0;
	for(u8 row = 0; row < 4; row++)
	{
		M_Dio_void_setPinValue(KP_rows[row], DIO_LOW);
		for(u8 col = 0; col < 4; col++)
		{
			if (M_Dio_en_getPinValue(KP_columns[col]) == DIO_LOW)
			{
				for (int i = 0; i < 10 && j < 2; i++)
				{
					if (M_Dio_en_getPinValue(KP_columns[col]) == DIO_LOW)
						j++;
					else
						j = 0;
				}
				if (j != 0)
				{
					while(M_Dio_en_getPinValue(KP_columns[col]) == DIO_LOW);
					M_Dio_void_setPinValue(KP_rows[row], DIO_HIGH);
#if KP_USE_AS == KP_CALCULATOR
					return KP_keys[row][col];

#elif KP_USE_AS == KP_NUMBERS
				return KP_keys[row][col];
#else
#error("Wrong Configuration")
#endif
//				while (M_Dio_en_getPinValue(KP_columns[col]) == DIO_LOW);
				}
			}
		}
		M_Dio_void_setPinValue(KP_rows[row], DIO_HIGH);
	}
	return KP_NO_PRESSED_KEY;
}
