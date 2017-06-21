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
	printf("CODA DEI TASK\n");
	if (head == NULL) {
		printf("VUOTA");
	} else {
		ReadyQueue *node = head;
		do {
			char buffer[100];
			getTaskDescription(&(node->task), buffer);
			printf("%s\nnext= %p\nprevious=%p\nmyAddress=%p\n-----------\n",
					buffer, node->next, node->previous, node);
			node = node->next;
		} while (node != NULL);
	}

}

