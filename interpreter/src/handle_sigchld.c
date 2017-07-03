#include <stdio.h>	//perror, NULL
#include <sys/wait.h>	//waitpid, pid_t, WNOHANG
#include <errno.h>	//errno
#include "header/handle_sigchld.h"
#include <stdlib.h>
void handle_sigchld() {
	pid_t pid;
	int saved_errno = errno;
	//ripeto il ciclo finchè ci sono processi che hanno terminato
	while ((pid = waitpid((pid_t) (-1), NULL, WNOHANG)) > 0) {
		printf("Il processo id:%d è terminato con successo.\n", pid);
		//(pid_t) (-1): attendi qualunque figlio
		//&status==NULL: non ci interessa lo stato di terminazione
		//WNOHANG: esci se il segnale non era un figlio che ha terminato (restituisce 0)
	}
	errno = saved_errno; //ripristino errno
}

