#include "header/modify.h"
#include "header/readyQueue.h"
#include "header/utilities.h"

int modifyById(ReadyQueue *head, unsigned long id) {
	ReadyQueue *found = searchById(head,id);
	if(found==NULL){
		printf("Task non trovato nel sistema");
		return 0;
	}
	int appo[2] = { 0, 9 };
	printf("\nPriorità attuale:%d\nInserisci la nuova priorità (tra 0 e 9): ",found->task.priority);
	byte priority = selectOption(appo, NULL, 0);
	found->task.priority = priority;
	return 1;
}

