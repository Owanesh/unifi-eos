#include "header/changeScheduling.h"
#include "header/readyQueue.h"

int policyScheduling = POLICY_PRIORITY;

void changeScheduling(ReadyQueue *head) {
	policyScheduling = ((policyScheduling - 1) * -1);
}

void bubbleSort(ReadyQueue **head) {

}
