#include "header/modify.h"
#include "header/readyQueue.h"
#include "header/utilities.h"

byte requestPriority(ReadyQueue* found);

/*
 * Modifica la priorità del task specificato, ritorna 1 in caso di successo, altrimenti 0
 */
int modifyById(ReadyQueue *head, unsigned long id) {
	if (isEmpty(head)) {
		printf("La lista dei task e' vuota.");
		return 0;
	}
	ReadyQueue *found = searchById(head, id);
	if (found == NULL) {
		printf("Task non trovato nel sistema.");
		return 0;
	}
	byte priority = requestPriority(found);
	found->task.priority = priority;
	return 1;
}

byte requestPriority(ReadyQueue* found) {
	int appo[2] = { 0, 9 };
	printf("\nPriorita' attuale:%d", found->task.priority);
	byte priority = selectOption("\nInserisci la nuova priorita' (tra 0 e 9): ",
			appo, NULL, 0);
	return priority;
}
