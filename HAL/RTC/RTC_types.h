/*
 * RTC_types.h
 *
 *  Created on: Mar 12, 2023
 *      Author: musta
 */

#ifndef HAL_RTC_RTC_TYPES_H_
#define HAL_RTC_RTC_TYPES_H_

typedef struct
{
	u8 hours;
	u8 minutes;
	u8 seconds;
}RTC_time_type;

typedef struct
{
	u16 year;
	u8 month;
	u8 dayInMonth;
	u8 dayInWeek;
}RTC_date_type;



#endif /* HAL_RTC_RTC_TYPES_H_ */
