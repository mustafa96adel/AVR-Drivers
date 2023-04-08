/*
 * TIMER1_priv.h
 *
 *  Created on: Mar 2, 2023
 *      Author: musta
 */

#ifndef TIMER1_TIMER1_PRIV_H_
#define TIMER1_TIMER1_PRIV_H_

#define Timer1_Set(value)          TCNT1  = value
#define Timer1_OCR_A_Set(value)      OCR1A  = value
#define Timer1_OCR_B_Set(value)      OCR1B  = value
#define Timer1_ICR_Set(value)     ICR1   = value

#endif /* TIMER1_TIMER1_PRIV_H_ */
