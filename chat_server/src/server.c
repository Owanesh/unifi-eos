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

void initClient(Client *client);

void start() {
	createPipe(server_pipe_name);
	server_pipe = openReadPipe(server_pipe_name);
}

void stop() {
	closeConnection(server_pipe, server_pipe_name);
}

int getServerPipe() {
	return server_pipe;
}

/* Ritorna la path completa della pipe all'interno del sistema
 * defaultPath + pipeName
 *
 * Funzione fondamentale per creare il parametro PipeName spesso
 * richiesto nelle funzioni
 */
char* pipeFullPath(char* name) {
	static char completePipeName[53];
	strcpy(completePipeName, defaultpath);
	strcat(completePipeName, name);
	return completePipeName;
}

/* Passando il nome della pipe che vogliamo, la apre in lettura*/
int openReadPipe(char* pipeName) {
	int openedPipe = open(pipeName, O_RDONLY | O_NONBLOCK); //salvo la pipe per la chiusura
	if (openedPipe == -1) {
		printf("\n[ERROR] (%s) Pipe creata ma inutilizzabile", pipeName);
	} else if (verboseMode == 1) {
		printf("\n[LOG] (%s) La pipe è pronta!", pipeName);
		fflush(stdout);
	}
	return openedPipe;
}

/* Inizializza il valore pipe di un Client*/
void initClient(Client *client) {
	int fd = 0;
	do { /* Prova ad aprire la pipe fino a che non ci riesce */
		fd = open(pipeFullPath(getClientPipeName(client->pid)), O_WRONLY); /* Apre la pipe in scrittura */
		if (fd == -1)
			sleep(1); /* Ci riprova dopo una secondo */
	} while (fd == -1);
	client->pipe = fd;
}

/* Dato un client, e un messaggio, si scrive sulla relativa pipe*/
void writeOnPipe(Client *client, char* message) {
	int fd, messageLen;
	messageLen = strlen(message) + 1;
	if (client->pipe == -1)
		initClient(client);
	write(client->pipe, message, messageLen); /* Scrive il messaggio nella pipe */
}

/* Ritorna il nome completo della pipe di un client
 * pid + _client_pipe */
char* getClientPipeName(pid_t pid) {
	static char pipePath[50];
	char base_string[] = "_client_pipe";
	sprintf(pipePath, "%d%s", pid, base_string);
	return pipePath;
}

/* Scorre la lista dei client, stampando tutti i pid che trova.
 * Ogni pid che trova corrisponde ad un utente connesso */
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

/* Ritorna l'ultimo client della lista, cosi da semplificare l'inserimento
 * di un nuovo Client */
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

/*
 * Legge il comando ricevuto in server_pipe, inserendolo in "str"
 */
void readCommand(char *str) {
	int dim = 512;
	/* non essendo possibile prevedere la lunghezza massima del messaggio ricevuto
	 * si alloca dinamicamente lo spazio del buffer
	 */
	str = realloc(str, sizeof(char) * dim);
	int n, count = 0;
	do { // Legge fino a '\0' o EOF
		n = read(server_pipe, str, 1);
		if (n != 0) {
			count++;
			if (count == dim) {
				//rialloco il doppio della dimensione precedente
				str = realloc(str, sizeof(char) * (dim * 2));
				dim *= 2;
				str += (count - 1); //riposiziono il puntatore
			}
		}
	} while (n > 0 && *str++ != '\0');
}
/*
 * Acquisisce il primo campo della stringa ricevuta,
 * ovvero la keyword che identifica il tipo di comando e
 * la inserisce nella variabile keyword
 */
void getFirstField(char keyword[20], char* cmd) {
	int i = 0;
	while (*cmd != ' ') {
		keyword[i] = *cmd;
		cmd++;
		i++;
	}
	keyword[i] = '\0';

}
