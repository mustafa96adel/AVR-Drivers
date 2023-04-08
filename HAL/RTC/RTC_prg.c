/*
 * RTC_prg.c
 *
 *  Created on: Mar 12, 2023
 *      Author: musta
 */

#include "avr/delay.h"
#include "STD_TYPES.h"
#include "I2C_int.h"
#include "RTC_priv.h"
#include "RTC_int.h"
#include "LCD_int.h"
extern I2C_config_type I2C_config;
void H_RTC_voidInit(void)
{
	M_I2C_voidInit(&I2C_config);
}

void H_RTC_voidSetTime(RTC_time_type time)
{
	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_START_COND_TRANSMITTED);

	M_I2C_voidSendByte(0xD0);
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_WRT_ACK);

	M_I2C_voidSendByte(0);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendByte(RTC_INCODE_VALUE_ELEMENT(time.seconds));
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendByte(RTC_INCODE_VALUE_ELEMENT(time.minutes));
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendByte(RTC_INCODE_VALUE_ELEMENT(time.hours));
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendStop();
	_delay_ms(1);
}

RTC_time_type H_RTC_getTime(void)
{
	RTC_time_type time;
	u8 valueReveived;
	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_START_COND_TRANSMITTED);

	M_I2C_voidSendByte(0xD0);
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_WRT_ACK);

	M_I2C_voidSendByte(0);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_REPEATED_START_TRANSMITTED);

	M_I2C_voidSendByte(0xD1);
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_READ_ACK);

	valueReveived = M_I2C_u8ReceiveByteACK();
	time.seconds = RTC_DECODE_VALUE_ELEMENT(valueReveived);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_RECEIVED_ACK);

	valueReveived = M_I2C_u8ReceiveByteACK();
	time.minutes = RTC_DECODE_VALUE_ELEMENT(valueReveived);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_RECEIVED_ACK);

	valueReveived = M_I2C_u8ReceiveByteNACK();
	time.hours = RTC_DECODE_VALUE_ELEMENT(valueReveived);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_RECEIVED_NACK);

	M_I2C_voidSendStop();
	return time;
}

void H_RTC_voidSetDate(RTC_date_type date)
{
	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_START_COND_TRANSMITTED);

	M_I2C_voidSendByte(0xD0);
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_WRT_ACK);

	M_I2C_voidSendByte(3);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendByte(RTC_INCODE_VALUE_ELEMENT(date.dayInWeek));
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendByte(RTC_INCODE_VALUE_ELEMENT(date.dayInMonth));
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendByte(RTC_INCODE_VALUE_ELEMENT(date.month));
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendByte(RTC_INCODE_VALUE_ELEMENT(date.year));
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);

	M_I2C_voidSendStop();
}

RTC_date_type H_RTC_getDate(void)
{
	RTC_date_type date;
	u8 valueReveived = 0;
	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_START_COND_TRANSMITTED);

	M_I2C_voidSendByte(0xD0);
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_WRT_ACK);

	M_I2C_voidSendByte(3);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_TRANSMITTED_ACK);
	M_I2C_voidSendStart();
	while(M_I2C_u8GetStatus() != I2C_MASTER_REPEATED_START_TRANSMITTED);

	M_I2C_voidSendByte(0xD1);
	while(M_I2C_u8GetStatus() != I2C_MASTER_SLA_ADD_READ_ACK);

	valueReveived = M_I2C_u8ReceiveByteACK();
	date.dayInWeek = RTC_DECODE_VALUE_ELEMENT(valueReveived);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_RECEIVED_ACK);

	valueReveived = M_I2C_u8ReceiveByteACK();
	date.dayInMonth = RTC_DECODE_VALUE_ELEMENT(valueReveived);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_RECEIVED_ACK);

	valueReveived = M_I2C_u8ReceiveByteACK();
	date.month = RTC_DECODE_VALUE_ELEMENT(valueReveived);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_RECEIVED_ACK);

	valueReveived = M_I2C_u8ReceiveByteNACK();
	date.year = RTC_DECODE_VALUE_ELEMENT(valueReveived);
	while(M_I2C_u8GetStatus() != I2C_MASTER_BYTE_RECEIVED_NACK);

	M_I2C_voidSendStop();
	return date;

}
