#include "header/execute.h"
#include "header/readyQueue.h"

void execute(ReadyQueue *tail) {

}
void executeById(ReadyQueue *head, unsigned long id) {
	ReadyQueue *found = searchById(head,id);
	if(found==NULL){
		printf("Task non trovato nel sistema");
		return;
	}
	found->task.exec_cycles --;
}
