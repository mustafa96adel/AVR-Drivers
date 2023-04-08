/*
 * OS_prg.c
 *
 *  Created on: Mar 24, 2023
 *      Author: musta
 */


#include "STD_TYPES.h"
#include "TIMER0_int.h"
#include "OS_cfg.h"
#include "OS_types.h"
#include "OS_priv.h"
#include "OS_int.h"

#define TASK(ID)		(tasks[ID/OS_MAX_PRIORITY][ID % OS_MAX_TASKS_PER_PRIORITY])

static taskID_type currentTaskID = 0;

#if OS_DEBUG

#include "LCD_int.h"
u32 tasksStartTime[OS_MAX_PRIORITY][OS_MAX_TASKS_PER_PRIORITY];

#endif

static OS_task_type tasks[OS_MAX_PRIORITY][OS_MAX_TASKS_PER_PRIORITY];
static u8 lastEmptyIndex[OS_MAX_PRIORITY];

static volatile u32 OS_counter = 0;
static volatile u32 taskCounters[OS_MAX_PRIORITY][OS_MAX_TASKS_PER_PRIORITY];
static volatile u8 start;

taskID_type OS_createTask(void (*taskHandler)(void) ,u32 periodicity, u8 priority, u32 firstDelay)
{
	tasks[priority][lastEmptyIndex[priority]].func = taskHandler;
	tasks[priority][lastEmptyIndex[priority]].state = WAITING;
	tasks[priority][lastEmptyIndex[priority]].periodicity = periodicity;
	tasks[priority][lastEmptyIndex[priority]].priority = priority;
	tasks[priority][lastEmptyIndex[priority]].firstDelay = firstDelay;
	lastEmptyIndex[priority]++;
	return priority * OS_MAX_TASKS_PER_PRIORITY + lastEmptyIndex[priority] - 1;		// returns task ID
}

static void schedule()
{
	for(s8 i = 0; i < OS_MAX_PRIORITY; i++)
	{
		for (s8 j = 0; j < lastEmptyIndex[i]; j++)
		{
			if (tasks[i][j].state == SUSPENDED_FOR_DELAY)
			{
				taskCounters[i][j]--;
				if (taskCounters[i][j] == 0)
				{
					tasks[i][j].state = READY;
					start = 1;
				}
			}
			else if((((OS_counter - tasks[i][j].firstDelay) % tasks[i][j].periodicity) == 0) && (OS_counter >= tasks[i][j].firstDelay) && ( tasks[i][j].state != SUSPENDED))
			{
#if OS_DEBUG
				tasksStartTime[i][j] = OS_counter;
#endif
				tasks[i][j].state = READY;
				start = 1;
			}
		}
	}
	OS_counter += OS_TICK;
	if (OS_counter % OS_TICK != 0)			// check for counter overflow
		OS_counter = 0;
}

void OS_voidInit(void)
{
	timer0_config_t t = {TIMER0_NORMAL_MODE, TIMER0_COMPARE_OUTPUT_NON_PWM_NORMAL_MODE, TIMER0_CLOCK_SELECT_IO_CLOCK_DIV_BY_1024, 100};
	M_Timer0_void_Init(&t);
	M_Timer0_void_setOverFlowCallBack(schedule);
	M_GI_enable();
	M_Timer0_void_EnablOverFloweInt();
	M_Timer0_void_setDelayTimeMilliSec(OS_TICK);
//	M_Timer0_void_start();
}

void OS_voidRun(void)
{
	M_Timer0_void_start();
	while(1)
	{
		while (start == 0);
		start = 0;
		for(s8 i = 0; i < OS_MAX_PRIORITY; i++)
		{
			for (s8 j = 0; j < lastEmptyIndex[i]; j++)
			{
				if (tasks[i][j].state == READY)
				{
#if OS_DEBUG
					if (OS_counter - OS_TICK != tasksStartTime[i][j])
					{
						u32 lateness = OS_counter - OS_TICK - tasksStartTime[i][j];
						H_LCD_void_sendCommand(LCD_CMD_CLEAR);
						H_LCD_void_sendString("ERROR : Late ExecuteFor Task Number ");
						H_LCD_void_sendIntNum(i * OS_MAX_TASKS_PER_PRIORITY + j);
						H_LCD_void_gotoXY(2, 0);
						H_LCD_void_sendString("ready time ");
						H_LCD_void_sendIntNum(tasksStartTime[i][j]);
						H_LCD_void_gotoXY(3, 0);
						H_LCD_void_sendString("start time ");
						H_LCD_void_sendIntNum(lateness);
						while(1);
					}
#endif

					tasks[i][j].state = RUNNING;
					currentTaskID = i * OS_MAX_TASKS_PER_PRIORITY + j;
					tasks[i][j].func();
					tasks[i][j].state = WAITING;
				}
			}
		}
	}
}
void OS_voidDelay(taskID_type taskID, u16 numOfTicks)
{
	tasks[taskID / OS_MAX_PRIORITY][taskID % OS_MAX_TASKS_PER_PRIORITY].state = SUSPENDED_FOR_DELAY;
	taskCounters[taskID/OS_MAX_PRIORITY][taskID % OS_MAX_TASKS_PER_PRIORITY] = numOfTicks;
}

void OS_voidSuspend(taskID_type taskID)
{
	TASK(taskID).state = SUSPENDED;
}

void OS_voidResume(taskID_type taskID)
{
	TASK(taskID).state = WAITING;
}
