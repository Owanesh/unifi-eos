#include "header/changeScheduling.h"
#include "header/readyQueue.h"
#include "header/utilities.h"

void swap(ReadyQueue *left, ReadyQueue *right);
int compare_policy(struct ReadyQueue *a, struct ReadyQueue *b);

int policyScheduling = POLICY_PRIORITY;

/* @parameters (ReadyQueue *head)
 * @explanation:
 * Change policy scheduling and sort list
 */
void changeScheduling(ReadyQueue *head) {
	policyScheduling = ((policyScheduling - 1) * -1);
	bubbleSort(&head);
}


/* @parameters (ReadyQueue *a, ReadyQueue *b)
 * @returns : {0,-1,1}
 * 		0 : two elements have equal values
 * 		1 : A is major than B
 * 	   -1 : A is minor than B
 * @explanation:
 * This function make a comparison between two nodes of list.
 * Comparison Parameter will be selected dynamically on base of policyScheduling variables
 */
int compare_policy(ReadyQueue *a, ReadyQueue *b) {
	if (policyScheduling)
		return a->task.exec_cycles < b->task.exec_cycles ? -1 :
				a->task.exec_cycles > b->task.exec_cycles ? 1 : 0;
	else
		return a->task.priority < b->task.priority ? -1 :
				a->task.priority > b->task.priority ? 1 : 0;
}


void bubbleSort(ReadyQueue **headQueue) {
	bool swapped;
	struct ReadyQueue *current;
	struct ReadyQueue *previous = NULL;

	if (*headQueue == NULL)
		return;
	do {
		swapped = false;
		current = *headQueue;
		while (current->next != previous) {
			if (compare_policy(current, current->next) > 0) {
				swap(current, current->next);
				if (current == *headQueue) { //swapped on head of queue
					(*headQueue) = current->previous;
				}
				swapped = true;
			} else {
				current = current->next;
			}
		}
		previous = current;
	} while (swapped);
}



void swap(ReadyQueue *left, ReadyQueue *right) {
	ReadyQueue *appo1, *appo2;
	appo1 = (left == right->next) ? right : right->next;
	appo2 = (right == left->next) ? left : left->next;
	left->next = appo1;
	right->next = appo2;
	appo1 = (left == right->previous) ? right : right->previous;
	appo2 = (right == left->previous) ? left : left->previous;
	left->previous = appo1;
	right->previous = appo2;
	if (left->next)
		left->next->previous = left;
	if (left->previous)
		left->previous->next = left;
	if (right->next)
		right->next->previous = right;
	if (right->previous)
		right->previous->next = right;
}
