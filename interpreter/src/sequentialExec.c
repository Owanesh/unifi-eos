#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "header/sequentialExec.h"
#include "header/readCommand.h"
void sequentialExec() {
	char* command;
	pid_t pid;
	do {
		command = readCommand();
		if (command != NULL) {
			if ((pid = fork()) == 0) {
				//processo figlio

			} else {
				//processo padre
				int status;
				wait(&status);
				if (WIFEXITED(status))
					printf("Il processo id:%d è terminato con successo.\n",
							pid);
			}
		}
	} while (command != NULL);
}
