/*
 * ADC_types.h
 *
 *  Created on: Mar 3, 2023
 *      Author: musta
 */

#ifndef MCAL_ADC_ADC_TYPES_H_
#define MCAL_ADC_ADC_TYPES_H_

typedef enum
{
	ADC_AREF,
	ADC_AVCC,
	ADC_INTERNAL_2_56_V = 3
}ADC_v_ref_type;

typedef enum
{
	ADC_RIGHT_ADJUST,
	ADC_LEFT_ADJUST
}ADC_adjust_type;

typedef enum
{
	ADC_SINGLE_TRIGGER,
	ADC_AUTO_TRIGGER
}ADC_trig_type;
typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	ADC0_ADC0_10x,
	ADC1_ADC0_10x,
	ADC0_ADC0_200x,
	ADC1_ADC0_200x,
	ADC2_ADC2_10x,
	ADC3_ADC2_10x,
	ADC2_ADC2_200x,
	ADC3_ADC_200x,
	ADC0_ADC1_1x,
	ADC1_ADC1_1x,
	ADC2_ADC1_1x,
	ADC3_ADC1_1x,
	ADC4_ADC1_1x,
	ADC5_ADC1_1x,
	ADC6_ADC1_1x,
	ADC7_ADC1_1x,
	ADC0_ADC2_1x,
	ADC1_ADC2_1x,
	ADC2_ADC2_1x,
	ADC3_ADC2_1x,
	ADC4_ADC2_1x,
	ADC5_ADC2_1x,
	VBG_1_22,
	GND
}ADC_channel_id_type;

typedef enum
{
	ADC_FREE_RUNNING,
	ADC_ANALOG_COMPARATOR,
	ADC_EXTERNAL_INT_REQ_0,
	ADC_TIMER0_CMP_MATCH,
	ADC_TIMER0_OVERFLOW,
	ADC_TIMER1_CMP_MATCH_B,
	ADC_TIMER1_OVERFLOW,
	ADC_TIMER1_CAPTURE
}ADC_auto_trigger_source_type;

typedef enum
{
	ADC_DIV_BY_2 = 1,
	ADC_DIV_BY_4,
	ADC_DIV_BY_8,
	ADC_DIV_BY_16,
	ADC_DIV_BY_32,
	ADC_DIV_BY_64,
	ADC_DIV_BY_128,
}ADC_prescaler_types;

typedef struct
{
	ADC_v_ref_type ref;
	ADC_adjust_type adjust;
	ADC_trig_type trigger;
	ADC_channel_id_type id;
	ADC_prescaler_types prescaler;
	ADC_auto_trigger_source_type auto_trig_source;
}ADC_config_type;
#endif /* MCAL_ADC_ADC_TYPES_H_ */
