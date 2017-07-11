#include <stdio.h>
#include <stdlib.h>
#include "header/utilities.h"
#include "header/server.h"
#include <sys/stat.h>           /* For S_IFIFO */
#include <fcntl.h>
#include <unistd.h> /* unlink */
#include <string.h>
#include "header/client.h"
#include "header/disconnect.h"
#include "header/connect.h"


int server_pipe;
char* server_pipe_name = "server_pipe";
char* defaultpath = "../";


void start() {
	createPipe(server_pipe_name);
	server_pipe = openRPipe(server_pipe_name);
 }
void stop() {
	closeConnection(server_pipe, server_pipe_name);
}

int getServerPipe() {
	return server_pipe;
}



/* Return complete path of pipe
 * defaultPath + pipeName
 */
char* pipeFullPath(char* name) {
	static char completePipeName[53];
	strcpy(completePipeName, defaultpath);
	strcat(completePipeName, name);
	return completePipeName;
}


/* Passando il nome della pipe che vogliamo, la apre in lettura*/
int openRPipe(char* pipeName) {
	int openedPipe = open(pipeName, O_RDONLY | O_NONBLOCK); //salvo la pipe per la chiusura
	if (openedPipe == -1) {
		printf("\n[ERROR] (%s) Pipe creata ma inutilizzabile", pipeName);
	} else if (verboseMode == 1) {
		printf("\n[LOG] (%s) La pipe è pronta!", pipeName);
		fflush(stdout);
	}
	return openedPipe;
}

/* Ritorna il nome completo della pipe di un client
 * pid + _client_pipe */
char* clientPname(pid_t pid) {
	static char pipePath[50];
	char base_string[] = "_client_pipe";
	sprintf(pipePath, "%d%s", pid, base_string);
	return pipePath;
}




void connectedClientList(Client *head) {
	if (head == NULL) {
		printf("\n *** NESSUN UTENTE CONNESSO ***");
		return;
	} else {
		Client *cloneHead = (head);
		printf("\n*** LISTA UTENTI CONNESSI ***");
		do {
			printf("\n %d", cloneHead->pid);
			fflush(stdout);
			cloneHead = cloneHead->next;
		} while (cloneHead != NULL);
	}
}

Client* getLastClient(Client *head) {
	if (head == NULL) {
		return NULL;
	}
	Client *last = head;
	while (last->next != NULL) {
		last = last->next;
	}
	return last;
}

int readCommand(int fd, char *str) {
	/* ALL CMD ARE [<CMD> ]
	 * CMD + whitespace */

	int n;
	do { /* Read characters until ' ' or end-of-input */
		n = read(fd, str, 1); /* Read one character */
	} while (n > 0 && *str++ != ' ');
	return (n > 0); /* Return false if end-of-input */
}
