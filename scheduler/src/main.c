#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header/task.h"
#include "header/utilities.h"

const char *options[] = { "(1) Crea un nuovo task",
		"(2) Esegui il task in testa alla coda", "(3) Esegui un task specifico",
		"(4) Elimina un task specifico", "(5) Modifica la priorita di un task",
		"(6) Cambiare la politica di scheduling utilizzata",
		"(7) Uscire dal programma", NULL };

void switchOptions(int value) {
	switch (value) {
	case 1:
		insertNewTask();
		break;
	case 2:
		execute();
		break;
	case 3:
		int id = selectOption( NULL, NULL, 0);
		executeById(id);
		break;
	case 4:
		int id = selectOption( NULL, NULL, 0);
		deleteById(id);
		break;
	case 5:
		int id = selectOption( NULL, NULL, 0);
		modifyById(id);
		break;
	case 6:
		changeScheduling();
		break;

	}
}
int main() {
	int optionsAllowed[] = { 1, 7 };
	int value;
	do {
		printMenu(options, "Scheduler C", "Busiello and Mauro", false, true,
				50);
		value = selectOption(optionsAllowed, NULL, 0);
		switchOptions(value);
	} while (value != 7);
	return 0;
}

