#include "header/readyQueue.h"
#include "header/delete.h"
#include <stdlib.h>

int handleSpecialCase(ReadyQueue **head, ReadyQueue *task);
void deleteLastNode(ReadyQueue **head);
void deleteHead(ReadyQueue **head, ReadyQueue * task);
void deleteTail(ReadyQueue *task);

/*
 * Elimina il task specificato, ritorna 1 in caso di successo, altrimenti 0
 */
int deleteById(ReadyQueue **head, unsigned long id) {
	if (isEmpty(*head)) {
		printf("La coda dei task e' vuota.");
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
 * Elimina il task specificato.
 * Ritorna 1 in caso di successo, altrimenti 0
 */
int delete(ReadyQueue **head, ReadyQueue *task) {
	if (isEmpty(*head)) {
		printf("La coda dei task e' vuota.");
		return 0;
	}
	int done = handleSpecialCase(head, task);
	//se done==true allora l'eliminazione è già stata effettuata
	if (!done) {
		task->next->previous = task->previous;
		ReadyQueue *memoryToBeFreed = task->previous->next;
		task->previous->next = task->next;
		free(memoryToBeFreed);
	}
	return 1;
}

/*
 * Determina se l'eliminazione ricade in uno dei seguenti casi:
 * - rimozione unico nodo della lista
 * - rimozione primo elemento
 * - rimozione ultimo elemento
 */
int handleSpecialCase(ReadyQueue **head, ReadyQueue *task) {
	int done = 0;
	if (task->next == NULL && task->previous == NULL) {
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
	ReadyQueue *memoryToBeFreed = *head;
	*head = task->next;
	(*head)->previous = NULL;
	free(memoryToBeFreed);
}
void deleteTail(ReadyQueue *task) {
	free(task->previous->next);
	task->previous->next = NULL;
}
