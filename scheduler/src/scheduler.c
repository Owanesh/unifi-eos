#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "utilities.h"
#include "schedulerFunctions.h"

int testTask() {
	Task* t = NULL;
	char buffer[256];
	t = malloc(sizeof(Task));
	if (t != NULL) {
		setTask(t, 1, "Processo", 1, 1);
		getTaskDescription(t, buffer);
		printf("%s", buffer);
		free(t);
	} else {
		printf("ERRORE");
	}
	return 0;
}

int main() {
	testTask();
	/* TEST OF MAIN MENU */
	 printMainMenu();
	/* TEST OF <GET INTEGER FROM STDIN>*/
	int allowed[2] = { 1, 7 };
	int disabled[] = { 2,3,4,5,6 };
	int myInt;
	bool valid=false;
	while (!valid) {
		printf("\nInserisci la tua scelta > ");
		scanf("%d", &myInt);
		if (!isIntegerAllowed(myInt, allowed, disabled)) {
			printf("Il valore inserito, non risulta valido. Riprovare");
		}else{
			valid = true;
		}
	}
}

