#include <stdio.h>
#include <stdlib.h>
#include "header/task.h"
#include "header/utilities.h"
#include "header/schedulerFunctions.h"

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

	/* TEST OF MAIN MENU */
	printMainMenu();
	/* TEST OF <GET INTEGER FROM STDIN>*/
	int allowed[] = { 1, 7 };
	int disabled[] = { 1, 2 };

	int myInt;
	bool valid = false;
	while (!valid) {
		printf("\nInserisci la tua scelta > ");
		scanf("%d", &myInt);
		if (!isIntegerAllowed(myInt, allowed, disabled,
				LENGTH_ARRAY(disabled))) {
			printf("Il valore inserito, non risulta valido. Riprovare");
		} else {
			valid = true;
		}
	}
}

