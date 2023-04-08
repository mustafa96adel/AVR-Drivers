/*
 * OS_priv.h
 *
 *  Created on: Mar 25, 2023
 *      Author: musta
 */

#ifndef SERVICES_OS_PRIV_H_
#define SERVICES_OS_PRIV_H_

typedef enum
{
	DORMANT,
	READY,
	SUSPENDED,
	RUNNING,
	WAITING,
	SUSPENDED_FOR_DELAY
}OS_state_type;

typedef struct
{
	u32 periodicity;
	u32 firstDelay;
	void (*func)(void);
	u8 priority;
	OS_state_type state;
} OS_task_type;

#endif /* SERVICES_OS_PRIV_H_ */
