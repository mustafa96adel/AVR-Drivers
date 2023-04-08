/*
 * Mcu_HW.h
 *
 *  Created on: Feb 17, 2023
 *      Author: aya_enan
 */
/*****************************************************************/
/* FILE DESCRIPTION:
----------------------------------------------------------------
*  file     : Mcu_HW.h
*
*  breif    : this file contains all registers addresses
*
*****************************************************************
*/
#ifndef MCU_HW_H_
#define MCU_HW_H_
/******************************************
  INCLUDES
*******************************************/
#include "STD_TYPES.h"
/******************************************
  Global Data TYPES AND STRUCTURES
*******************************************/


/******************************************
  GLOBAL CONSTANT MACROS
*******************************************/
//-------------------DIO-------------------



#define PORTA_REG  (*((volatile u8*)0x3B))
#define DDRA_REG  (*((volatile u8*)0x3A))
#define PINA_REG  (*((volatile u8*)0x39))

#define PORTB_REG  (*((volatile u8*)0x38))
#define DDRB_REG  (*((volatile u8*)0x37))
#define PINB_REG  (*((volatile u8*)0x36))

#define PORTC_REG  (*((volatile u8*)0x35))
#define DDRC_REG  (*((volatile u8*)0x34))
#define PINC_REG  (*((volatile u8*)0x33))

#define PORTD_REG  (*((volatile u8*)0x32))
#define DDRD_REG  (*((volatile u8*)0x31))
#define PIND_REG  (*((volatile u8*)0x30))

//------------------ END of DIO------------
//////////////////////////////////////////////////
//---------------------EXTERNAL INTERRUPT-----------------------
#define MCUCR_REG  (*((volatile u8*)0x55))
#define MCUCSR_REG  (*((volatile u8*)0x54))
#define GICR		(*((volatile u8*)0x5B))
#define GIFR		(*((volatile u8*)0x5A))


#define SREG		(*((volatile u8*)0x5F))
//--------------END OF EXTERNAL INTERRUPTS---------------------
//////////////////////////////////////////////////////
//------------------------TIMER 0------------------------------
#define SFIOR         (*((volatile u8*)0x50))
#define TCCR0         (*((volatile u8*)0x53))
#define TCNT0         (*((volatile u8*)0x52))
#define OCR0          (*((volatile u8*)0x5C))
#define TIMSK         (*((volatile u8*)0x59))
#define TIFR          (*((volatile u8*)0x58))
//------------------END OF TIMER0------------------------------
////////////////////////////////////////////////
//----------------------TIMER1---------------------------------

#define TCCR1A        (*((volatile u8*)0x4F))
#define TCCR1B        (*((volatile u8*)0x4E))
#define TCNT1H        (*((volatile u8*)0x4D))
#define TCNT1L        (*((volatile u8*)0x4C))
#define TCNT1LH       (*((volatile u16*)0x4C))
#define OCR1AH        (*((volatile u8*)0x4B))
#define OCR1AL        (*((volatile u8*)0x4A))
#define OCR1BH        (*((volatile u8*)0x49))
#define OCR1BL        (*((volatile u8*)0x48))
#define ICR1H         (*((volatile u8*)0x47))
#define ICR1L         (*((volatile u8*)0x46))
//---------------END OF TIMER1---------------------
///////////////////////////////////////////////////////
//---------------------ADC--------------------------
#define ADMUX         (*((volatile u8*)0x27))
#define ADCSRA        (*((volatile u8*)0x26))
#define ADCH          (*((volatile u8*)0x25))
#define ADCL          (*((volatile u8*)0x24))
//---------------END OF ADC----------------------------
//////////////////////////////////////////////////////
//-----------------------UART-----------------------
/*UART Registers*/
#define UDR  	*((volatile u8*)(0x2C))

#define UCSRA  	*((volatile u8*)(0x2B))
#define UCSRA_RXC_BIT	7
#define UCSRA_TXC_BIT	6
#define UCSRA_UDRE_BIT	5
#define UCSRA_FE_BIT	4
#define UCSRA_DOR_BIT	3
#define UCSRA_PE_BIT	2
#define UCSRA_U2X_BIT	1
#define UCSRA_MPCM_BIT	0

#define UCSRB  				*((volatile u8*)(0x2A))
#define UCSRB_RXCIE_BIT		7
#define UCSRB_TXCIE_BIT		6
#define UCSRB_UDRIE_BIT		5
#define UCSRB_RXEN_BIT		4
#define UCSRB_TXEN_BIT		3
#define UCSRB_UCSZ2_BIT		2
#define UCSRB_RXB8_BIT		1
#define UCSRB_TXB8_BIT		0

#define UCSRC_UBRRH  		*((volatile u8*)(0x40))
#define UCSRC_URSEL_BIT		7		//1 to use as UCSRC and 0 to use as UBRRH
#define UCSRC_UMSEL_BIT		6
#define UCSRC_UPM1_BIT		5
#define UCSRC_UPM0_BIT		4
#define UCSRC_USBS_BIT		3
#define UCSRC_UCSZ1_BIT		2
#define UCSRC_UCSZ0_BIT		1
#define UCSRC_UCPOL_BIT		0

#define UBRRL  	*((volatile u8*)(0x29))
//---------------END OF UART-----------------------
/////////////////////////////////////////////////////
//----------------------I2C------------------------
#define TWBR		  (*((volatile u8*)0x20))
#define TWCR		  (*((volatile u8*)0x56))
#define TWSR		  (*((volatile u8*)0x21))
#define TWDR		  (*((volatile u8*)0x23))
#define TWAR		  (*((volatile u8*)0x22))

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/
#endif /* MCU_HW_H_ */
