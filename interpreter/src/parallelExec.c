#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>	//sigaction, sigemptyset, struct sigaction, SIGCHLD, SA_RESTART, SA_NOCLDSTOP
#include "header/utilities.h"
#include "header/parallelExec.h"
#include "header/handle_sigchld.h" //funzione handler
#include "header/readCommand.h"
void bind_handler_sigchld();
void createFileP(int count);

void parallelExec() {
	signal(SIGUSR1, SIG_IGN); //ignoro SIGUSR1 perchè serve solo per evitare race condition
	bind_handler_sigchld(); // imposto l'handler opportuno per i SIGCHLD
	printf("Nota: Premere INVIO per terminare\n");
	int termination_flag = 0;
	int count = 0;
	pid_t pidPadre = getpid();
	do {
		printf("\n> ");
		//acquisizione comando da parte dell'utente
		char* str = readCommand();
		if (str != NULL) {
			termination_flag = 1;
			count++; //incremento dell'indice degli output file
			if (fork() == 0) {
				//processo figlio
				//la memoria dinamica istanziata in parseCommand sara'
				//liberata automaticamente al termine di questo processo figlio
				int saved_stdout = dup(STDOUT_FILENO);//in caso di errore mantengo STDOUT
				char **command = parseCommand(str);
				//il comando è stato salvato localmente, segnalo al padre il via libera al prossimo comando
				kill(pidPadre, SIGUSR1);
				createFileP(count);
				//l'ouput è redirezionato anche dopo execvp
				if (execvp(command[0], command) == -1) {
					//errore nell'esecuzione di execvp (probabilmente comando non riconosciuto)
					dup2(saved_stdout, STDOUT_FILENO);
					printf("Comando non riconosciuto.\n");
					exit(EXIT_FAILURE);
				}
			} else {
				//processo padre
				//devo almeno attendere che il figlio abbia copiato localmente il
				//comando da eseguire
				pause(); //aspettando SIGUSR1
			}
		} else {
			termination_flag = 0;
		}
	} while (termination_flag != 0);
}

void bind_handler_sigchld() {
	struct sigaction sa;
	sa.sa_handler = &handle_sigchld; //imposto la funzione da eseguire
	// impedisco a segnali come ^C o ^D di interrompere l'handler
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGSTOP);
	// gestisco SIGCHLD solo per figli che hanno terminato (non sospeso)
	sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	if (sigaction(SIGCHLD, &sa, 0) == -1) {
		//errore, uscita forzata
		perror(0);
		exit(EXIT_FAILURE);
	}
}

void createFileP(int count) {
	char fileName[100];
	if (argv[1] != '\0' && argv[1] != NULL) {
		char* path = "";
		if (argv[1][strlen(argv[1]) - 1] == '/')
			path = strcat(argv[1], "out.%d");
		else
			path = strcat(argv[1], "/out.%d");
		sprintf(fileName, path, count);
	} else {
		sprintf(fileName, "./src/output_file/out.%d", count);
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

