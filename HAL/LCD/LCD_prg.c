
#include <avr/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"
#include "LCD_int.h"

//static u8 row = 0, col = 0;			u may use them to fix ur location

static void latch(u8 data)
{
#if LCD_4BIT_MODE == 1
	M_Dio_void_setPinValue(LCD_D7, GET_BIT(data, 7));
	M_Dio_void_setPinValue(LCD_D6, GET_BIT(data, 6));
	M_Dio_void_setPinValue(LCD_D5, GET_BIT(data, 5));
	M_Dio_void_setPinValue(LCD_D4, GET_BIT(data, 4));

	M_Dio_void_setPinValue(LCD_EN, DIO_HIGH);
	_delay_us(1000);
	M_Dio_void_setPinValue(LCD_EN, DIO_LOW);
	_delay_ms(5);
	M_Dio_void_setPinValue(LCD_D7, GET_BIT(data, 3));
	M_Dio_void_setPinValue(LCD_D6, GET_BIT(data, 2));
	M_Dio_void_setPinValue(LCD_D5, GET_BIT(data, 1));
	M_Dio_void_setPinValue(LCD_D4, GET_BIT(data, 0));

	M_Dio_void_setPinValue(LCD_EN, DIO_HIGH);
	_delay_us(1000);
	M_Dio_void_setPinValue(LCD_EN, DIO_LOW);
	_delay_ms(5);
	#elif
	M_Dio_void_setPinValue(LCD_D7, GET_BIT(data, 7));
	M_Dio_void_setPinValue(LCD_D6, GET_BIT(data, 6));
	M_Dio_void_setPinValue(LCD_D5, GET_BIT(data, 5));
	M_Dio_void_setPinValue(LCD_D4, GET_BIT(data, 4));

	M_Dio_void_setPinValue(LCD_D3, GET_BIT(data, 3));
	M_Dio_void_setPinValue(LCD_D2, GET_BIT(data, 2));
	M_Dio_void_setPinValue(LCD_D1, GET_BIT(data, 1));
	M_Dio_void_setPinValue(LCD_D0, GET_BIT(data, 0));

	M_Dio_void_setPinValue(LCD_EN, DIO_HIGH);
	_delay_us(1000);
	M_Dio_void_setPinValue(LCD_EN, DIO_LOW);

#endif
}

void H_LCD_void_Init(void)
{
	_delay_ms(30);
	M_Dio_void_setPinValue(LCD_RS, DIO_LOW);
#if LCD_4BIT_MODE == 1
	H_LCD_void_sendCommand(0b00100010);

	M_Dio_void_setPinValue(LCD_D7, 1);
	M_Dio_void_setPinValue(LCD_D6, 0);

	M_Dio_void_setPinValue(LCD_EN, DIO_HIGH);
	_delay_us(1000);
	M_Dio_void_setPinValue(LCD_EN, DIO_LOW);
	_delay_ms(5);
#else
	H_LCD_void_sendCommand(0x18);
#endif
	H_LCD_void_sendCommand(0x0F);
	H_LCD_void_sendCommand(0x01);
	H_LCD_void_sendCommand(0x02);
//	H_LCD_void_sendCommand(LCD_CMD_CLEAR);
}

void H_LCD_void_sendCommand(u8 copy_u8command)
{
	M_Dio_void_setPinValue(LCD_RS, DIO_LOW);
	latch(copy_u8command);
}

void H_LCD_void_sendData(u8 copy_u8data )
{
	M_Dio_void_setPinValue(LCD_RS, DIO_HIGH);
	latch(copy_u8data);
}

void H_LCD_void_sendString(const s8 * pstr)
{
	while(*pstr != '\0')
	{
		H_LCD_void_sendData(*pstr);
		pstr++;
	}
}

void H_LCD_void_sendIntNum(s32 copy_s32Num)
{
	u8 numOfDigits = 0, i = 0;
	s8 num[10];
	if (copy_s32Num == 0)
	{
		H_LCD_void_sendData('0');
		return;
	}
	if (copy_s32Num < 0)
	{
		H_LCD_void_sendData('-');
		copy_s32Num *= -1;
	}
	s32 temp = copy_s32Num;
	while(temp)
	{
		temp /= 10;
		numOfDigits++;
	}
	temp = copy_s32Num;
	for (; i < numOfDigits; i++)
	{
		num[numOfDigits - i - 1] = LCD_CHAR_OF(temp % 10);
		temp /= 10;
	}
	num[numOfDigits] = '\0';
	H_LCD_void_sendString(num);
}

void H_LCD_void_gotoXY(u8 copy_u8Row,u8 copy_u8Col)
{
	u8 address = copy_u8Row * 20 + copy_u8Col;

	H_LCD_void_sendCommand(SET_BIT(address, 7));
}

void H_LCD_void_creatCustomChar (const u8 * ArrPattern,u8 copy_u8charCode)
{
	H_LCD_void_sendCommand(copy_u8charCode * 8 + 0b01000000);
	for(int i = 0; i < 8; i++)
	{
		H_LCD_void_sendData(ArrPattern[i]);
	}
	H_LCD_void_sendCommand(0x80);
//	H_LCD_void_sendCommand(LCD_CMD_RETURN_HOME);
}

void H_LCD_void_displayCustomChar (u8 copy_u8charCode)
{
	H_LCD_void_sendData(copy_u8charCode);
}
