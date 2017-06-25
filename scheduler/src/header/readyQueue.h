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
 * Restituisce un puntatore al Task identificato da 'id, altrimenti NULL.
 */
ReadyQueue* searchById(ReadyQueue *head, unsigned long id);
/*
 * Restituisce il puntatore all'ultimo nodo della lista se non vuota, altrimenti NULL
 */
ReadyQueue* getLastNode(ReadyQueue *head);

/*
 * Restituisce 1 se la lista è vuota, altrimenti 0
 */
int isEmpty(ReadyQueue *head);

void printList(ReadyQueue *head);

#endif /* HEADER_READYQUEUE_H_ */
