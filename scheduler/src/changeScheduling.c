#include "header/changeScheduling.h"
#include "header/readyQueue.h"

int policyScheduling = 0;

void changeScheduling(ReadyQueue *head) {
	policyScheduling = ((policyScheduling-1)*-1);
}

void bubbleSort(ReadyQueue **head){

}
