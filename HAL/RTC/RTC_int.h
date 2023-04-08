/*
 * RTC_int.h
 *
 *  Created on: Mar 12, 2023
 *      Author: musta
 */

#ifndef HAL_RTC_RTC_INT_H_
#define HAL_RTC_RTC_INT_H_
#include "RTC_types.h"

void H_RTC_voidInit(void);
void H_RTC_voidSetTime(RTC_time_type time);
RTC_time_type H_RTC_getTime(void);

void H_RTC_voidSetDate(RTC_date_type date);
RTC_date_type H_RTC_getDate(void);
#endif /* HAL_RTC_RTC_INT_H_ */
