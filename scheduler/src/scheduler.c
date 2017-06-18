#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "utilities.h"

int main() {
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
