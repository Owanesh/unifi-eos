#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "header/utilities.h"
#include "header/sequentialExec.h"
#include "header/readCommand.h"
void createFile(int count);

void sequentialExec() {
	printf("Nota: Premere INVIO per terminare\n");
	int termination_flag = 0;
	int count = 0;
	pid_t pid;
	do {
		printf("\n> ");
		//acquisizione comando da parte dell'utente
		char* str = readCommand();
		if (str != NULL) {
			termination_flag = 1;
			count++; //incremento dell'indice degli output file
			if ((pid = fork()) == 0) {
				//processo figlio
				//la memoria dinamica istanziata in parseCommand sara'
				//liberata automaticamente al termine di questo processo figlio
				int saved_stdout = dup(STDOUT_FILENO);//in caso di errore mantengo STdOUT
				char **command = parseCommand(str);
				createFile(count);
				//l'ouput è redirezionato anche dopo execvp
				if (execvp(command[0], command) == -1) {
					//errore nell'esecuzione di execvp (probabilmente comando non riconosciuto)
					dup2(saved_stdout, STDOUT_FILENO);
					printf("Comando non riconosciuto.\n");
					exit(EXIT_FAILURE);
				}
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
		} else {
			termination_flag = 0;
		}
		free(str);
	} while (termination_flag != 0);
}

void createFile(int count) {
	char fileName[100];
	if (argv[1] != '\0' && argv[1] != NULL) {
		char* path = "";
		if (argv[1][strlen(argv[1]) - 1] == '/')
			path = strcat(argv[1], "out.%d");
		else
			path = strcat(argv[1], "/out.%d");
		sprintf(fileName, path, count);
	} else {
		sprintf(fileName, "./output_file/out.%d", count);
	}

//crea il file se non esiste, altrimenti truncate. Permesso di lettura/scrittura per l'owner
	int fd = open(fileName, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0) {
		perror("Apertura file: ");
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1); // redirezione dell'output su stdout
	close(fd);
}
