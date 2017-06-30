#include <stdio.h>
#include "header/sequentialExec.h"
#include "header/readCommand.h"
void sequentialExec() {
	char* command;
	do {
		command = readCommand();
	} while (command != NULL);
}

