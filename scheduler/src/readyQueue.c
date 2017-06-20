#include "header/task.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct ReadyQueue {
	Task task;
	struct ReadyQueue *next;
} ReadyQueue;

/*
 * Returns the pointer to a Task searched by Id. Returns NULL if not found.
 * If previous != NULL and exists a task with the specified Id, then previous will contain the previous
 * element (useful foe elimination)
 */
ReadyQueue* searchById(ReadyQueue *head, unsigned long id,
		ReadyQueue **previous) {
	ReadyQueue* p = head;
	if (previous != NULL)
		*previous = head;
	ReadyQueue* rst = NULL;
	int found = 0;
	while (!found && p != NULL) {
		if (p->task.id == id) {
			rst = p;
			found = 1;
			//caso particolare, l'elemento cercato è head quindi previous = NULL
			if (previous != NULL && *previous == head && rst == head) {
				//*previous era un puntatore allocato dinamicamente, devo liberare la memoria
				free(*previous);
				*previous = NULL;
			}
		}
		if (previous != NULL && !found) {
			*previous = p;
		}
		p = p->next;
	}
	if (rst == NULL) {
		free(*previous);
		*previous = NULL;
	}
	return rst;
}
