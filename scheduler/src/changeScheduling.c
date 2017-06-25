#include "header/changeScheduling.h"
#include "header/readyQueue.h"
#include "header/utilities.h"

void swap(ReadyQueue *left, ReadyQueue *right);

int compare_policy(ReadyQueue *left, ReadyQueue *right);

int policyScheduling = POLICY_PRIORITY;

/*
 * Cambia la politica di scheduling attuale
 */
void changeScheduling() {
	policyScheduling = ((policyScheduling + 1) % 2);
}

/*
 * Realizza l'ordinamento della lista attraverso bubblesort
 */
void bubbleSort(ReadyQueue **headQueue) {
	if (isEmpty(*headQueue))
		return;

	bool swapped;
	ReadyQueue *current;
	do {
		swapped = false;
		current = *headQueue;
		while (current->next != NULL) {
			if (compare_policy(current, current->next) > 0) {
				swap(current, current->next);
				if (current == *headQueue) {
					//è stata modificata la testa della lista
					(*headQueue) = current->previous;
				}
				swapped = true;
			} else {
				current = current->next;
			}
		}
	} while (swapped);
}

/*
 * Determina se i due nodi debbano essere scambiati, in base alla politica di scheduling corrente.
 */
int compare_policy(ReadyQueue *left, ReadyQueue *right) {
	// Priority = DESC   //Exec_Cycles = ASC
	// If Equal value : Sort by ID DESC
	if (policyScheduling == POLICY_EXEC_CYCLES) {
		return left->task.exec_cycles > right->task.exec_cycles ? 1 :
				left->task.exec_cycles < right->task.exec_cycles ? -1 :
				left->task.id < right->task.id ? 1 : -1;
	} else {
		return left->task.priority > right->task.priority ? -1 :
				left->task.priority < right->task.priority ? 1 :
				left->task.id < right->task.id ? 1 : -1;
	}

}

/* Scambia due nodi all'interno della lista
 * scambiando anche i rispettivi puntatori ai successivi e precedenti nodi
 */
void swap(ReadyQueue *left, ReadyQueue *right) {
	//MAX 6 puntatori da modificare,
	//se left è il primo nodo o right è l'ultimo nodo della lista diventano 5,
	//se entrambi i casi diventano 4.
	if (right->next != NULL) {
		right->next->previous = left;
	}
	if (left->previous != NULL) {
		left->previous->next = right;
	}
	left->next = right->next;
	right->next = left;
	right->previous = left->previous;
	left->previous = right;
}

