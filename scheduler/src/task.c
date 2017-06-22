#include "header/task.h"
#include <stdio.h>
#include <string.h>

unsigned long id = 1;

/* Return 0 if parameters are invalid, otherwise value!=0 */
int setTask(Task* t, char* name, byte priority, byte exec_cycles) {
	int valid = (priority >= 0 && priority <= 9)
			&& (exec_cycles >= 1 && exec_cycles <= 99);
	if (valid) {
		t->id = id++;
		strcpy(t->name, name);
		t->priority = priority;
		t->exec_cycles = exec_cycles;
	}
	return valid;
}

void getTaskDescription(Task* t, char* buffer) {
	sprintf(buffer, "ID: %lu\nName: %s\nPriority: %d\nExecution cycles: %d",
			t->id, t->name, t->priority, t->exec_cycles);
}

