#include <stdlib.h>
#include "header/insert.h"
#include "header/changeScheduling.h"
#include "header/utilities.h"
#include "header/readyQueue.h"

void requestData(char *name, byte *priority, byte *exec_cycles);
void requestName(char *name);
void addTask(ReadyQueue **head, char *name, byte priority, byte exec_cycles);

/*
 * Inserts a new Task in the list passed as argument
 */
void insertNewTask(ReadyQueue **head) {
	char name[9];
	byte priority, exec_cycles;
	requestData(name, &priority, &exec_cycles);
	addTask(head, name, priority, exec_cycles);
}

void requestData(char *name, byte *priority, byte *exec_cycles) {
	requestName(name);

	int appo[2] = { 0, 9 };
	*priority = selectOption("Inserisci priorita' (tra 0 e 9): ", appo, NULL, 0);

	appo[0] = 1;
	appo[1] = 99;
	*exec_cycles = selectOption("Inserisci cicli di esecuzione (tra 1 e 99): ",
			appo, NULL, 0);
}

void requestName(char *name) {
	int rc = OK;
	do {
		printf("Inserisci nome (MAX 8 caratteri): ");
		rc = getLine(name, sizeof(char[9]));
		if (rc == TOO_LONG) {
			printf("Nome troppo lungo. Riprovare.\n");
		} else if (rc == NO_INPUT) {
			printf("Nessun carattere inserito. Riprovare.\n");
		} else if (rc == INVALID) {
			printf("Nome non valido (evita spazi o invio) . Riprovare.\n");
		}
	} while (rc != OK);
}

void addTask(ReadyQueue **head, char *name, byte priority, byte exec_cycles) {
	if (isEmpty(*head)) {
		*head = malloc(sizeof(ReadyQueue));
		(*head)->next = NULL;
		(*head)->previous = NULL;
		setTask(&((*head)->task), name, priority, exec_cycles);
	} else {
		ReadyQueue *last = getLastNode(*head);
		last->next = malloc(sizeof(ReadyQueue));
		last->next->next = NULL; //last pointer has no successor
		last->next->previous = last; //set link to the ex-last
		setTask(&(last->next->task), name, priority, exec_cycles);
	}
}
