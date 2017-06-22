#include "header/readyQueue.h"
#include "header/delete.h"
#include <stdlib.h>

int handleSpecialCase(ReadyQueue **head, ReadyQueue *task);
void deleteLastNode(ReadyQueue **head);
void deleteHead(ReadyQueue **head, ReadyQueue * task);
void deleteTail(ReadyQueue *task);

/*
 * Deletes the task specified by id, returns 1 in case of success, otherwise 0 (i.e. taks not found)
 */
int deleteById(ReadyQueue **head, unsigned long id) {
	if (isEmpty(*head)) {
		printf("La coda dei task è vuota.");
		return 0;
	}
	ReadyQueue *found = searchById(*head, id);
	if (found == NULL) {
		printf("Task non trovato.");
		return 0;
	}
	delete(head, found);
	return 1;
}

/*
 * Deletes the task passed as argument (head might be changed so it's necessary to the function)
 * Returns 1 in case of success, otherwise 0 (head is empty)
 */
int delete(ReadyQueue **head, ReadyQueue *task) {
	if (isEmpty(*head)) {
		printf("La coda dei task è vuota.");
		return 0;
	}
	int done = handleSpecialCase(head, task);

	if (!done) {
		task->next->previous = task->previous;
		ReadyQueue *memoryToBeFreed = task->previous->next; //saving the pointer
		task->previous->next = task->next;
		free(memoryToBeFreed);
	}
	return 1;
}

int handleSpecialCase(ReadyQueue **head, ReadyQueue *task) {
	int done = 0;
	if (task->next == NULL && task->previous == NULL) {
		//there's only one element
		deleteLastNode(head);
		done = 1;
	} else if (task->next == NULL) {
		deleteTail(task);
		done = 1;
	} else if (task->previous == NULL) {
		deleteHead(head, task);
		done = 1;
	}
	return done;
}
void deleteLastNode(ReadyQueue **head) {
	free(*head);
	*head = NULL;
}

void deleteHead(ReadyQueue **head, ReadyQueue * task) {
	ReadyQueue *memoryToBeFreed = *head; //saving the pointer
	*head = task->next; //modify the head
	(*head)->previous = NULL;
	free(memoryToBeFreed);
}
void deleteTail(ReadyQueue *task) {
	free(task->previous->next);
	task->previous->next = NULL;
}
