#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "header/sequentialExec.h"
#include "header/readCommand.h"
void createFile(int count);

void sequentialExec() {
	int count = 0;
	char* command;
	pid_t pid;
	do {
		printf("\n> ");
		command = readCommand();
		if (command != NULL) {
			count++; //incremento dell'indice degli output file
			if ((pid = fork()) == 0) {
				//processo figlio
				createFile(count);
				char *args = "date";
				char *argv[] = { "+%Y-%m-%d", NULL };
				execvp(args, argv); //l'ouput è redirezionato anche dopo execvp
			} else {
				//processo padre
				int status;
				wait(&status);
				if (WIFEXITED(status))
					printf("Il processo id:%d è terminato con successo.\n",
							pid);
				else {
					perror("Errore processo: ");
				}

			}
		}
	} while (command != NULL);
}

void createFile(int count) {
	char fileName[100];
	sprintf(fileName, "src/output_file/out.%d", count);
	//crea il file se non esiste, altrimenti truncate. Permesso di scrittura per l'owner
	int fd = open(fileName, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0) {
		perror("Apertura file: ");
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1); // redirezione dell'output su stdout
	close(fd);
}

