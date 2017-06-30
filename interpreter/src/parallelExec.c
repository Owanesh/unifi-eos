#include <signal.h>	//sigaction, sigemptyset, struct sigaction, SIGCHLD, SA_RESTART, SA_NOCLDSTOP
#include "header/parallelExec.h"
#include "header/handle_sigchld.h" //funzione handler
#include "header/readCommand.h"
void bind_handler_sigchld();

void parallelExec() {
	bind_handler_sigchld(); // imposto l'handler opportuno

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
		exit(1);
	}
}
