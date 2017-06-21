#ifndef HEADER_READYQUEUE_H_
#define HEADER_READYQUEUE_H_

#include "task.h"
#include <stdio.h>
typedef struct ReadyQueue {
	Task task;
	struct ReadyQueue *next;
	struct ReadyQueue *previous;
} ReadyQueue;

/*
 * Returns the pointer to a Task searched by Id. Returns NULL if not found.
 * If previous != NULL and exists a task with the specified Id, then previous will contain the previous
 * element (useful foe elimination)
 */
ReadyQueue* searchById(ReadyQueue *head, unsigned long id);
/*
 * Get the last element of the list if it's not empty, otherwise NULL
 */
ReadyQueue* getLastNode(ReadyQueue *head);

/*
 * Returns 1 if the list is empty, otherwise 0 (NOTE: you have to pass the head of the list)
 */
int isEmpty(ReadyQueue *head);

void printList(ReadyQueue *head);

#endif /* HEADER_READYQUEUE_H_ */
