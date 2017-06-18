/*
 * task.c
 *
 *  Created on: 18 giu 2017
 *      Author: matteomauro
 */
#include "task.h" //types "Task" and "byte" defined here
#include <stdio.h>
#include <string.h>

void setTask(Task* t, unsigned long id, char* name, byte priority,
		byte exec_cycles) {
	t->id = id;
	strcpy(t->name, name);
	t->priority = priority;
	t->exec_cycles = exec_cycles;
}

void getTaskDescription(Task* t, char* buffer) {
	sprintf(buffer, "ID: %lu\nName: %s\nPriority: %d\nExecution cycles: %d",
			t->id, t->name, t->priority, t->exec_cycles);
}

