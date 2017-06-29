#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>	//sigaction, sigemptyset, struct sigaction, SIGCHLD, SA_RESTART, SA_NOCLDSTOP
#include "header/handle_sigchld.h"

char* readCommand() {
	char *str;
	int ch, size = 21, len = 0;
	str = realloc(NULL, sizeof(char) * size); //20 caratteri disponibili + '\0'
	if (str == NULL) //errore
		return str;
	while ((ch = fgetc(stdin)) != EOF && ch != '\n') { //lettura fino a EOF o '\n'
		str[len++] = ch;
		if (len == size) {
			str = realloc(str, sizeof(char) * (size += 16)); //rialloco 15 caratteri + '\0'
			if (str == NULL) //errore
				return str;
		}
	}
	str[len++] = '\0'; //terminazione stringa
	str = realloc(str, sizeof(char) * len); //rialloco esattamente lo spazio occupato
	return str;
}

void bind_handler_sigchld();

int main(void) {
	bind_handler_sigchld();
	char *m;
	printf("input string : ");
	m = readCommand();
	printf("%s\n", m);
	printf("length: %lu\n", strlen(m));
	printf("address: %p\n", m);
	free(m);
	return 0;
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
