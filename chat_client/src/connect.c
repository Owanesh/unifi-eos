#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "header/connect.h"
#include "header/main_client.h"

int sendRequestToServer();

/*
 * Apre la connessione al serverPipe ed al clientPipe, salvando i fd
 * nei riferimenti presenti in main_client.h.
 * Restituisce 1 se la connessione e' stata aperta con successo, altrimenti 0
 */
int connect() {
	int isConnected = sendRequestToServer();
	int rst = 0;
	if (isConnected) {
		//apertura del "<pid>_client_pipe"
		char pipePath[50];
		sprintf(pipePath, "%d", getpid());
		strcat(pipePath, "_client_pipe");
		do {
			//continua ad aprire finche' non ha successo
			fdClientPipe = open(pipePath, O_RDONLY);
			sleep(1);
		} while (fdClientPipe == -1);
		//da adesso fdClientPipe sara' attiva per comunicare con il server
		rst = 1;
	} else {
		printf("Errore di connessione (probabilmente server spento).\n");
	}
	return rst;
}

/*
 * Apre il server_pipe e invia i propri dati per richiedere accesso.
 * Restituisce 1 se il file esiste e viene aperto, altrimenti 0
 */
int sendRequestToServer() {
	char *serverPipePath = "server_pipe";
	// apre server_pipe in scrittura
	fdServerPipe = open(serverPipePath, O_WRONLY);
	if (fdServerPipe == -1) {
		return 0;
	}
	//da adesso fdServerPipe sara' attiva per comunicare con il server
	char msg[50];
	//richiesta-> "CONNECT <pid>"
	sprintf(msg, "%s %d", "CONNECT", getpid());
	int msgLength = strlen(msg) + 1; //+1 per '\0'
	write(fdServerPipe, msg, msgLength);
	return 1;
}
