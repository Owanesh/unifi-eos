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
		char pipePath[25];
		sprintf(pipePath, "%d", getpid());
		strcat(pipePath, "_client_pipe");
		do {
			//continua ad aprire finche' non ha successo
			fdClientPipe = open(pipePath, O_RDONLY);
			sleep(1);
		} while (fdClientPipe == -1);
		rst = 1; //connessione riuscita
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
	int fd;
	char *serverPipePath = "server_pipe";
	// apre server_pipe in scrittura
	fd = open(serverPipePath, O_WRONLY);
	if (fd == -1) {
		return 0;
	}
	char msg[15];
	//richiesta-> "CONNECT <pid>"
	sprintf(msg, "%s %d", "CONNECT", getpid());
	int msgLength = strlen(msg);
	write(fd, msg, msgLength);
	return 1;
}
