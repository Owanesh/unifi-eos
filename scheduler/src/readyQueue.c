#include "header/task.h"
#include "header/readyQueue.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Returns the pointer to a Task searched by Id. Returns NULL if not found.
 *
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
 * Returns 1 if the list is empty, otherwise 0 (NOTE: you have to pass the head of the list)
 */
int isEmpty(ReadyQueue *head) {
	if (head == NULL)
		return 1;
	else
		return 0;
}

/*
 * Get the last element of the list if it's not empty, otherwise NULL
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
