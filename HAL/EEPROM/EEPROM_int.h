/*
 * EEPROM_int.h
 *
 *  Created on: Mar 11, 2023
 *      Author: musta
 */

#ifndef HAL_EEPROM_EEPROM_INT_H_
#define HAL_EEPROM_EEPROM_INT_H_
#include "STD_TYPES.h"

void H_EEPROM_voidInit(void);

void H_EEPROM_voidWriteByte(u16 address, u8 data);

u8 H_EEPROM_u8ReadByte(u16 address);


#endif /* HAL_EEPROM_EEPROM_INT_H_ */
