/*
 * RTC_priv.h
 *
 *  Created on: Mar 12, 2023
 *      Author: musta
 */

#ifndef HAL_RTC_RTC_PRIV_H_
#define HAL_RTC_RTC_PRIV_H_

#define RTC_INCODE_VALUE_ELEMENT(VALUE)		((VALUE % 10) + ((VALUE / 10) << 4))
#define RTC_DECODE_VALUE_ELEMENT(VALUE)		((VALUE & 0XF) + 10 * ((VALUE & 0x70) >> 4))
#endif /* HAL_RTC_RTC_PRIV_H_ */
