#include <stdlib.h>
#include "header/insert.h"
#include "header/utilities.h"
#include "header/readyQueue.h"

void requestData(char *name, byte *priority, byte *exec_cycles);
void requestName(char *name);
void addTask(ReadyQueue **head, char *name, byte priority, byte exec_cycles);

/*
 * Inserisce un nuovo task nella lista ricevuta
 */
void insertNewTask(ReadyQueue **head) {
	char name[9];
	byte priority, exec_cycles;
	requestData(name, &priority, &exec_cycles);
	addTask(head, name, priority, exec_cycles);
}

/* Richiede input numerici all'utente, imponendo i limiti entro i quali
 * viene considerato valido */
void requestData(char *name, byte *priority, byte *exec_cycles) {
	requestName(name);

	int appo[2] = { 0, 9 };
	*priority = selectOption("Inserisci priorita' (tra 0 e 9): ", appo, NULL,
			0);

	appo[0] = 1;
	appo[1] = 99;
	*exec_cycles = selectOption("Inserisci cicli di esecuzione (tra 1 e 99): ",
			appo, NULL, 0);
}

/* Valida un input di una stringa da parte dell'utente
 * Nel caso di un input non consistente vengono stampati gli opportuni
 * messaggi di errore */
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

/* Aggiunge un task all'interno della coda, allocando dinamicamente lo spazio
 * e facendo i collegamenti con i puntatori successivi e precedenti */
void addTask(ReadyQueue **head, char *name, byte priority, byte exec_cycles) {
	if (isEmpty(*head)) {
		//prima inizializzazione della lista
		*head = malloc(sizeof(ReadyQueue));
		(*head)->next = NULL;
		(*head)->previous = NULL;
		setTask(&((*head)->task), name, priority, exec_cycles);
	} else {
		//aggiunta in coda
		ReadyQueue *last = getLastNode(*head);
		last->next = malloc(sizeof(ReadyQueue));
		last->next->next = NULL;
		last->next->previous = last;
		setTask(&(last->next->task), name, priority, exec_cycles);
	}
}
