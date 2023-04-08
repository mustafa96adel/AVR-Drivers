/*
 * OS_int.h
 *
 *  Created on: Mar 24, 2023
 *      Author: musta
 */

#ifndef SERVICES_OS_INT_H_
#define SERVICES_OS_INT_H_
#include "STD_TYPES.h"
#include "OS_types.h"

taskID_type OS_createTask(void (*taskHandler)(void) ,u32 periodicity, u8 priority, u32 firstDelay);
void OS_voidInit(void);
void OS_voidRun(void);
void OS_voidDelay(taskID_type taskID, u16 numOfTicks);
void OS_voidSuspend(taskID_type taskID);
void OS_voidResume(taskID_type taskID);


#endif /* SERVICES_OS_INT_H_ */
