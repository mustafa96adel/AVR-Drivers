/*
 * TIMER1_int.h
 *
 *  Created on: Mar 2, 2023
 *      Author: musta
 */

#ifndef TIMER1_TIMER1_INT_H_
#define TIMER1_TIMER1_INT_H_

#include "TIMER1_types.h"



void TIMER1_Init(Timer1_Mode_Type mode, Timer1_Prescaler_Type scaler);
void TIMER1_InputCaptureEdge(ICU_Edge_type edge);
void TIMER1_OC1A_Mode(OC1A_Mode_type mode);
void TIMER1_OC1B_Mode(OC1B_Mode_type mode);


void M_TIMER1_ICU_InterruptEnable(void);
void M_TIMER1_ICU_InterruptDisable(void);

void M_TIMER1_OVF_InterruptEnable(void);
void M_TIMER1_OVF_InterruptDisable(void);

void M_TIMER1_OCA_InterruptEnable(void);
void M_TIMER1_OCA_InterruptDisable(void);

void M_TIMER1_OCB_InterruptEnable(void);
void M_TIMER1_OCB_InterruptDisable(void);

u16 M_TIMER1_Read(void);
u8  M_TIMER1_Read_OVF_Flag(void);

u16 M_TIMER1_OCR_A_Read(void);
u8  M_TIMER1_Read_OCU_A_Flag(void);

u16 M_TIMER1_OCR_B_Read(void);
u8  M_TIMER1_Read_OCU_B_Flag(void);

u16 M_TIMER1_ICR_Read(void);
u8  M_TIMER1_Read_ICU_Flag(void);


void M_TIMER1_SetCallBack(Timer1InterruptSource_type Interrupt, void(*Local_fptr)(void));
/************************************************************************************************************/

#endif /* TIMER1_TIMER1_INT_H_ */
