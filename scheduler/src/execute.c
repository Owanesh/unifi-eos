#include "header/execute.h"
#include "header/readyQueue.h"
#include "header/delete.h"
#include <string.h>

void checkTermination(ReadyQueue** head, ReadyQueue* task);

/*
 * Esegue il primto task della ReadyQueue (decrementa il numero cicli rimanenti),
 * Necessita della testa della coda e dell'id del task da eseguire
 */
void execute(ReadyQueue **head) {
	if (isEmpty(*head)) {
		printf("La lista dei task e' vuota.");
		return;
	}
	ReadyQueue *last = getLastNode(*head);
	last->task.exec_cycles--; //decremento delle esecuzioni di un'unità
	printf("Esecuzione avvenuta con successo.\n");
	checkTermination(head, last);
}

/*
 * Esegue il task specificato (decrementa il numero cicli rimanenti),
 * ritorna 1 in caso di successo, 0 altrimenti
 * Necessita della testa della coda e dell'id del task da eseguire
 */
void executeById(ReadyQueue **head, unsigned long id) {
	if (isEmpty(*head)) {
		printf("La lista dei task e' vuota.");
		return;
	}
	ReadyQueue *found = searchById(*head, id);
	if (found == NULL) {
		printf("Task non trovato nel sistema");
		return;
	}
	found->task.exec_cycles--; //decremento delle esecuzioni di un'unità
	printf("Esecuzione avvenuta con successo.\n");
	checkTermination(head, found);
}

/*
 * Verifica se task è terminato, in caso affermativo ne avvia l'eliminazione dalla lista
 */
void checkTermination(ReadyQueue** head, ReadyQueue* task) {
	if (task->task.exec_cycles == 0) {
		char name[9];
		strcpy(name, task->task.name);
		delete(head, task); //cancellazione delegata al modulo delete
		printf("Il task %s ha terminato la sua esecuzione.", name);
	}
}
