/*
 * TIMER1_prg.c
 *
 *  Created on: Mar 2, 2023
 *      Author: musta
 */
#include "avr/interrupt.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "TIMER1_types.h"
#include "TIMER1_priv.h"
#include "TIMER1_int.h"

void M_TIMER1_Init(Timer1_Mode_Type mode, Timer1_Prescaler_Type scaler)
{
	u8 TMP;
	//Select Mode
	TMP = GET_AFT_CLR_BITS(TCCR1A, 2, 0);
	TCCR1A = TMP | ((mode & 0x03) << 0);

	TMP = GET_AFT_CLR_BITS(TCCR1B, 2, 3);
	TCCR1B = TMP | ((mode>>2) << 3);

	//prescaler (clock)
	TMP = GET_AFT_CLR_BITS(TCCR1B, 3, 0);
	TCCR1B = TMP | (scaler<<0);

	TCCR1A = GET_AFT_CLR_BITS(TCCR1A, 4, 4); // OC1A, OC1B Disconnected
}

void M_TIMER1_OC1A_Mode(OC1A_Mode_type mode)
{
	u8 TMP;
	TMP = GET_AFT_CLR_BITS(TCCR1A, 2, 6);
	TCCR1A = TMP | (mode<<6);
}

void M_TIMER1_OC1B_Mode(OC1B_Mode_type mode)
{
	u8 TMP;
	TMP = GET_AFT_CLR_BITS(TCCR1A, 2, 4);
	TCCR1A = TMP | (mode<<4);
}

void M_TIMER1_InputCaptureEdge(ICU_Edge_type edge)
{
	WRITE_BIT(TCCR1B, 6, edge);
}

/*************************** Enable/Disable Functions **************************/
void M_TIMER1_ICU_InterruptEnable(void)
{
	SET_BIT(TIFR, 5);
	SET_BIT(TIMSK,5);
}
void M_TIMER1_ICU_InterruptDisable(void)
{
	CLR_BIT(TIMSK,5);
}

void M_TIMER1_OVF_InterruptEnable(void)
{
	SET_BIT(TIFR, 2);
	SET_BIT(TIMSK,2);
}
void M_TIMER1_OVF_InterruptDisable(void)
{

	CLR_BIT(TIMSK,2);
}

void M_TIMER1_OCA_InterruptEnable(void)
{
	SET_BIT(TIFR, 4);
	SET_BIT(TIMSK,4);
}
void M_TIMER1_OCA_InterruptDisable(void)
{
	CLR_BIT(TIMSK,4);
}

void M_TIMER1_OCB_InterruptEnable(void)
{
	SET_BIT(TIFR, 3);
	SET_BIT(TIMSK,3);
}
void M_TIMER1_OCB_InterruptDisable(void)
{
	CLR_BIT(TIMSK,3);
}

/*************************** Read/Write Functions **************************/
u16 M_TIMER1_Read(void)
{
	u16 temp = TCNT1L;
	temp += TCNT1H << 8;
	return temp;
}
u8  M_TIMER1_Read_OVF_Flag(void)
{
	return GET_BIT(TIFR,2);
}

u16 M_TIMER1_OCR_A_Read(void)
{
	u16 temp = OCR1AL;
		temp += OCR1AH << 8;
	return temp;
}
u8  M_TIMER1_Read_OCA_Flag(void)
{
	return GET_BIT(TIFR, 4);
}

u16 M_TIMER1_OCR_B_Read(void)
{
	u16 temp = OCR1BL;
		temp += OCR1BH << 8;
	return temp;
}
u8  M_TIMER1_Read_OCB_Flag(void)
{
	return GET_BIT(TIFR, 3);
}

u16 M_TIMER1_ICR_Read(void)
{
	u16 temp =  ICR1L;
		temp += ICR1H << 8;
	return temp;
}
u8  M_TIMER1_Read_ICU_Flag(void)
{
	return GET_BIT(TIFR, 5);
}

/*************************** Pointer to Functions to be assigned to ISR **************************/
//we make it static to not be edited by any one in another files
//concept of setter and getter
static void (*Fptr_OVF1_INT)(void) = NULL;
static void (*Fptr_OCA_INT)(void) = NULL;
static void (*Fptr_OCB_INT)(void) = NULL;
static void (*Fptr_ICU1_INT)(void) = NULL;
/**************************************** Call Back Functions ************************************/


void M_TIMER1_SetCallBack(Timer1InterruptSource_type Interrupt,void(*Local_fptr)(void))
{
	switch(Interrupt)
	{
		case TIMER1_OVF_INTERRUPT:
			Fptr_OVF1_INT=Local_fptr;
			break;
		case TIMER1_OCR_A_INTERRUPT:
			Fptr_OCA_INT=Local_fptr;
			break;
		case TIMER1_OCR_B_INTERRUPT:
			Fptr_OCB_INT=Local_fptr;
			break;
		case TIMER1_ICU_INTERRUPT:
			Fptr_ICU1_INT=Local_fptr;
			break;
	}
}
/********************************************** ISR **********************************************/
ISR(TIMER1_OVF_vect)
{
	if(Fptr_OVF1_INT != NULL)
	{
		Fptr_OVF1_INT();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(Fptr_OCA_INT != NULL)
	{
		Fptr_OCA_INT();
	}
}
ISR(TIMER1_COMPB_vect)
{
	if(Fptr_OCB_INT != NULL)
	{
		Fptr_OCB_INT();
	}
}
ISR(TIMER1_CAPT_vect)
{
	if(Fptr_ICU1_INT != NULL)
	{
		Fptr_ICU1_INT();
	}
}

