#include "header/task.h"
#include <stdio.h>
typedef struct ReadyQueue {
	Task task;
	struct ReadyQueue *next;
} ReadyQueue;

/*
 * Returns the pointer to a Task searched by Id. Returns NULL if not found.
 * If previous != NULL and exists a task with the specified Id, then previous will contain the previous
 * element (useful foe elimination)
 */
ReadyQueue* searchById(ReadyQueue *head, unsigned long id, ReadyQueue *previous) {
	ReadyQueue* p = head;
	ReadyQueue* rst = NULL;
	int found = 0;
	while (!found && p != NULL) {
		if (p->task.id == id) {
			rst = p;
			found = 1;
		}
		if (previous != NULL) {
			previous = p;
		}
		p = p->next;
	}
	return rst;
}
