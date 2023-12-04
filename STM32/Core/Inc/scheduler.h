/*
 * scheduler.h
 *
 *  Created on: Nov 29, 2023
 *      Author: lmchi
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include "toggleLed.h"
#include "counter.h"

typedef struct {
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} tasks;

//define const
#define SCH_MAX_TASKS 			40
#define	NO_TASK_ID				0
tasks SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Add_Tasks(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Delete_Tasks(int taskID);
void updateArrayTasks(int taskID);


#endif /* INC_SCHEDULER_H_ */
