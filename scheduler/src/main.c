#include <stdio.h>
#include <stdlib.h>
#include "header/task.h" //struttura di un task
#include "header/utilities.h" //funzioni di utilità
#include "header/readyQueue.h" //struttura della readyQueue
#include "header/insert.h"
#include "header/execute.h"
#include "header/delete.h"
#include "header/modify.h"
#include "header/changeScheduling.h" //dichiarazione della variabile policyScheduling

// opzioni del menù principale
const char* options[] = { "(1) Crea un nuovo task",
		"(2) Esegui il prossimo task", "(3) Esegui un task specifico",
		"(4) Elimina un task specifico", "(5) Modifica la priorita' di un task",
		"(6) Cambiare la politica di scheduling utilizzata",
		"(7) Uscire dal programma", NULL };

//puntatore alla testa della coda dei task
ReadyQueue *head = NULL;

/* Controlla la scelta dell'utente ed invoca le funzioni opportune */
void switchOptions(int value) {
	unsigned long id;
	switch (value) {
	case 1:
		insertNewTask(&head);
		bubbleSort(&head);
		break;
	case 2:
		execute(&head);
		if (policyScheduling == POLICY_EXEC_CYCLES) {
			// potrebbe richiedere una riordinazione
			bubbleSort(&head);
		}
		break;
	case 3:
		id = selectOption("\nInserire l'ID del task che si vuole eseguire: ",
		NULL, NULL, 0);
		executeById(&head, id);
		if (policyScheduling == POLICY_EXEC_CYCLES) {
			// potrebbe richiedere una riordinazione
			bubbleSort(&head);
		}
		break;
	case 4:
		id = selectOption("\nInserire l'ID del task che si vuole cancellare: ",
		NULL, NULL, 0);
		deleteById(&head, id);
		break;
	case 5:
		id = selectOption("\nInserire l'ID del task che si vuole modificare: ",
		NULL, NULL, 0);
		modifyById(head, id);
		if (policyScheduling == POLICY_PRIORITY) {
			// potrebbe richiedere una riordinazione
			bubbleSort(&head);
		}
		break;
	case 6:
		changeScheduling();
		bubbleSort(&head);
		break;
	}
}

void printPolicy() {
	printf("\nScheduling attuale: ");
	if (policyScheduling == POLICY_PRIORITY) {
		printf("Priorita'");
	} else {
		printf("Esecuzioni rimanenti");
	}
	printRow(50, '-');
}

int main() {
	int optionsAllowed[] = { 1, 7 };
	int value;
	do {
		printMenu(options, "Scheduler C", "Busiello and Mauro", false, true,
				50);
		printPolicy();
		value = selectOption("Selezionare un'opzione del menu': ",
				optionsAllowed, NULL, 0);
		switchOptions(value);
		printList(head);
	} while (value != 7);
	return 0;
}

