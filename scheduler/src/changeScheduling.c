#include "header/changeScheduling.h"
#include "header/readyQueue.h"
#include "header/utilities.h"

void swap(ReadyQueue *left, ReadyQueue *right);

int compare_policy(ReadyQueue *left, ReadyQueue *right);

int policyScheduling = POLICY_PRIORITY;

/*
 * Change policy scheduling
 */
void changeScheduling() {
	policyScheduling = ((policyScheduling + 1) % 2);
}

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
				if (current == *headQueue) { //swapped the head of queue
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
 * This function makes a comparison between two nodes of list.
 * Comparison Parameter will be selected dynamically on base of policyScheduling variable
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

void swap(ReadyQueue *left, ReadyQueue *right) {
	//MAX 6 pointers to change,
	//but if c is the last or b is the head they become 5,
	//if both the case then 4
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

