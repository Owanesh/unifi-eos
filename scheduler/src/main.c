#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header/task.h"
#include "header/utilities.h"
#include "header/readyQueue.h"
#include "header/insert.h"
#include "header/execute.h"
#include "header/delete.h"
#include "header/modify.h"
#include "header/changeScheduling.h"

const char* options[] = { "(1) Crea un nuovo task",
		"(2) Esegui il prossimo task", "(3) Esegui un task specifico",
		"(4) Elimina un task specifico", "(5) Modifica la priorita' di un task",
		"(6) Cambiare la politica di scheduling utilizzata",
		"(7) Uscire dal programma", NULL };

ReadyQueue *head = NULL;

void switchOptions(int value) {
	unsigned long id;
	switch (value) {
	case 1:
		insertNewTask(&head);
		break;
	case 2:
		execute(&head);
		if (policyScheduling == POLICY_EXEC_CYCLES) {
			// it might need to be sorted
			bubbleSort(&head);
		}
		break;
	case 3:
		id = selectOption("\nInserire l'ID del task che si vuole eseguire: ",
		NULL, NULL, 0);
		executeById(&head, id);
		if (policyScheduling == POLICY_EXEC_CYCLES) {
			// it might need to be sorted
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
			// it might need to be sorted
			bubbleSort(&head);
		}
		break;
	case 6:
		changeScheduling(head);
		break;
	}
}

int main() {
	int optionsAllowed[] = { 0, 7 };
	int value;
	do {
		printMenu(options, "Scheduler C", "Busiello and Mauro", false, true,
				50);
		value = selectOption("Selezionare un'opzione del menu': ",
				optionsAllowed, NULL, 0);
		switchOptions(value);
		printList(head);
	} while (value != 7);
	return 0;
}

