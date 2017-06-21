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
		"(2) Esegui il task in testa alla coda", "(3) Esegui un task specifico",
		"(4) Elimina un task specifico", "(5) Modifica la priorita di un task",
		"(6) Cambiare la politica di scheduling utilizzata",
		"(7) Uscire dal programma", NULL };

ReadyQueue *head = NULL, *tail = NULL;

void test() {
	head = (ReadyQueue*) malloc(sizeof(ReadyQueue));
	if (head != NULL) {
		setTask(&(head->task), "TASK_1", 1, 30);
		head->next = NULL;
		head->next = (ReadyQueue*) malloc(sizeof(ReadyQueue));
		if (head->next != NULL) {
			setTask(&(head->next->task), "TASK_2", 2, 50);
		}
	}
	ReadyQueue *rst = searchById(head, 3);
	if (rst != NULL) {
		char buffer[100];
		getTaskDescription(&(rst->task), buffer);
		printf("trovato %s\n", buffer);

	} else {
		printf("TASK NOT FOUND\n");
	}

}

void switchOptions(int value) {
	unsigned long id;
	switch (value) {
	case 1:
		insertNewTask(head);
		break;
	case 2:
		execute(tail);
		break;
	case 3:
		id = selectOption( NULL, NULL, 0);
		executeById(head, id);
		break;
	case 4:
		id = selectOption( NULL, NULL, 0);
		deleteById(head, id);
		break;
	case 5:
		id = selectOption( NULL, NULL, 0);
		modifyById(head, id);
		break;
	case 6:
		changeScheduling(head);
		break;
	case 0:
		test();
		break;

	}
}

int main() {
	int optionsAllowed[] = { 0, 7 };
	int value;
	do {
		printMenu(options, "Scheduler C", "Busiello and Mauro", false, true,
				50);
		value = selectOption(optionsAllowed, NULL, 0);
		switchOptions(value);
	} while (value != 7);
	return 0;
}

