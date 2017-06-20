#ifndef HEADER_READYQUEUE_H_
#define HEADER_READYQUEUE_H_

#include "task.h"
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
ReadyQueue* searchById(ReadyQueue *head, unsigned long id, ReadyQueue **previous);

#endif /* HEADER_READYQUEUE_H_ */
