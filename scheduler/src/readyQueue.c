#include "header/task.h"
#include "header/readyQueue.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Restituisce un puntatore al Task identificato da 'id, altrimenti NULL.
 */
ReadyQueue* searchById(ReadyQueue *head, unsigned long id) {
	ReadyQueue* p = head;
	ReadyQueue* rst = NULL;
	int found = 0;
	while (!found && p != NULL) {
		if (p->task.id == id) {
			rst = p;
			found = 1;
		}
		p = p->next;
	}
	return rst;
}

/*
 * Restituisce 1 se la lista è vuota, altrimenti 0
 */
int isEmpty(ReadyQueue *head) {
	if (head == NULL)
		return 1;
	else
		return 0;
}

/*
 * Restituisce il puntatore all'ultimo nodo della lista se non vuota, altrimenti NULL
 */
ReadyQueue* getLastNode(ReadyQueue *head) {
	if (isEmpty(head)) {
		return NULL;
	}
	ReadyQueue *last = head;
	while (last->next != NULL) {
		last = last->next;
	}
	return last;
}

/* Stampa in forma tabellare le informazioni relative ai task */
void printList(ReadyQueue *head) {
	if (head == NULL) {
		return;
	} else {
		printf("\n+----+-----------+-----------+-------------------+\n");
		printf("| ID | PRIORITA' | NOME TASK | ESECUZ. RIMANENTI |\n");
		printf("+----+-----------+-----------+-------------------+\n");
		ReadyQueue *node = head;
		do {
			printf("| %lu  |     %d     |   %s    |        %d         |\n",
					node->task.id, node->task.priority, node->task.name,
					node->task.exec_cycles);
			printf("+----+-----------+-----------+-------------------+\n");
			node = node->next;
		} while (node != NULL);
	}

}
