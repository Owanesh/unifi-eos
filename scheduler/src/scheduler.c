#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

	int allowed[] = { 1, 7 };
	int disabled[] = { 1, 2 };
	printMainMenu();
	int x = selectOption(allowed, disabled, LENGTH_ARRAY(disabled));
	printf("\nHai selezionato %d", x);
}

