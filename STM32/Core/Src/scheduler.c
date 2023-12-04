/*
 * scheduler.c
 *
 *  Created on: Nov 23, 2023
 *      Author: ADMIN
 */

#include "scheduler.h"

void SCH_Init(void){
	counter = 0;
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_Delete_Tasks(i);
    }
}

void SCH_Update(void) {
	if (SCH_tasks_G[0].pTask) {
		if (SCH_tasks_G[0].Delay == 0) {
			// Task is ready to run
			// Update flag
			SCH_tasks_G[0].RunMe += 1;
			if (SCH_tasks_G[0].Period) {
				// Update delay for task to run again
				SCH_tasks_G[0].Delay = SCH_tasks_G[0].Period;
			}
		}
		else {
			//Update delay for task
			SCH_tasks_G[0].Delay -= 1;
		}
	}
}

void SCH_Dispatch_Tasks(void) {
	while (SCH_tasks_G[0].RunMe > 0) {
		(*SCH_tasks_G[0].pTask)(); // Run task
		SCH_tasks_G[0].RunMe -= 1; // Update flag

		if (SCH_tasks_G[0].Period == 0) {
			// Remove one-shot task from the array
			SCH_Delete_Tasks(0);
		}
		else {
			tasks temp = SCH_tasks_G[0];
			SCH_Delete_Tasks(0);
			SCH_Add_Tasks(temp.pTask, temp.Delay, temp.Period);
		}
	}
}

void SCH_Add_Tasks(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	int id = 0;
	if (counter == 0){
		SCH_tasks_G[0].pTask = pFunction;
		SCH_tasks_G[0].Delay = DELAY;
		SCH_tasks_G[0].Period = PERIOD;
		SCH_tasks_G[0].RunMe = 0;
		counter++;
	}
	else if (counter > 0 && counter < SCH_MAX_TASKS){
		while ((id < counter) && (SCH_tasks_G[id].Delay <= DELAY)){
			DELAY -= SCH_tasks_G[id].Delay;
			id++;
		}
		if (id == counter){
			SCH_tasks_G[counter].pTask = pFunction;
			SCH_tasks_G[counter].Delay = DELAY;
			SCH_tasks_G[counter].Period = PERIOD;
			SCH_tasks_G[counter].RunMe = 0;
			counter++;
		}
		else {
			for (int i = counter; i > id; i--){
				SCH_tasks_G[i] = SCH_tasks_G[i - 1];
				SCH_tasks_G[i].Delay -= DELAY;
			}
			SCH_tasks_G[id].pTask = pFunction;
			SCH_tasks_G[id].Delay = DELAY;
			SCH_tasks_G[id].Period = PERIOD;
			SCH_tasks_G[id].RunMe = 0;
			counter++;
		}
	}
}

void SCH_Delete_Tasks(int taskID){
	if (taskID < counter - 1){
		updateArrayTasks(taskID);
	}
	else if (taskID == counter - 1){
	    SCH_tasks_G[taskID].pTask = 0;
	    SCH_tasks_G[taskID].Delay = 0;
	    SCH_tasks_G[taskID].Period = 0;
	    SCH_tasks_G[taskID].RunMe = 0;
	    counter--;
	}
}

void updateArrayTasks(int taskID){
	while (taskID < counter - 1){
		SCH_tasks_G[taskID] = SCH_tasks_G[taskID + 1];
		taskID++;
	}
    SCH_tasks_G[taskID].pTask = 0;
    SCH_tasks_G[taskID].Delay = 0;
    SCH_tasks_G[taskID].Period = 0;
    SCH_tasks_G[taskID].RunMe = 0;
    counter--;
}

