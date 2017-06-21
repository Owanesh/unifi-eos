#include "header/task.h"
#include "header/readyQueue.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Returns the pointer to a Task searched by Id. Returns NULL if not found.
 *
 */
ReadyQueue* searchById(ReadyQueue *head, unsigned long id) {
	ReadyQueue* p = head;
	ReadyQueue* rst = NULL;
	int found = 0;
	while (!found && p != NULL) {
		if (p->task.id == id) {
			rst = p;
			found = 1;
		}
		p = p->next;
	}
	return rst;
}
