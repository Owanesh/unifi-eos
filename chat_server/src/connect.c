#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>           /* For S_IFIFO */
#include <unistd.h> /* unlink */
#include <fcntl.h>

#include "header/client.h"
#include "header/connect.h"
#include "header/utilities.h"
#include "header/server.h"

void getPidFromCmd(char* cmd, pid_t* pid);
int isAlreadyConnected(Client **head, pid_t pid);
void addClientInList(Client **head, pid_t pid, char* path);

void acceptConnection(Client **head, char* cmd) {
	pid_t pid;
	getPidFromCmd(cmd, &pid);
	if (!isAlreadyConnected(head, pid)) {
		if (verboseMode == 1) {
			printf("\n[LOG] Request from %d accepted", pid);
			fflush(stdout);
		}
		char path[50];
		getClientPipePath(pid, path);
		createPipe(path);
		addClientInList(head, pid, path);
	} else if (verboseMode == 1) {
		printf("\n[WARNING] %d is already connected ", pid);
		fflush(stdout);
	}
}

/* Determina se un client e' gia' connesso.
 * Restituisce
 * 1: Pid gia' presente nella lista
 * 0: Pid non presente nella lista
 */
int isAlreadyConnected(Client **head, pid_t pid) {
	if ((*head) == NULL) {
		return 0;
	} else {
		Client *chead = (*head);
		do {
			if (chead->pid == pid) {
				return 1;
			}
			chead = chead->next;
		} while (chead != NULL);
	}
	return 0;
}

/*
 *  Crea una pipe individuata dal percorso "pipePath" e ne acquisisce i permessi "0660"
 */
void createPipe(char* pipePath) {
	//rimuovo la vecchia sessione del server
	if (unlink(pipePath) == -1) {
		printf(
				"\n[ERROR] (%s) Errore durante la rimozione della vecchia sessione",
				pipePath);
	} else if (verboseMode == 1) {
		printf("\n[LOG] (%s) Rimossa sessione precedente", pipePath);
		fflush(stdout);
	}
	//creo la nuova pipe
	if (mknod(pipePath, S_IFIFO, 0) < 0) {
		printf("\n[ERROR] (%s) Errore durante la generazione del pipe",
				pipePath);
	} else if (verboseMode == 1) {
		printf("\n[LOG] (%s) Generata nuova sessione", pipePath);
		fflush(stdout);

	}
	//acquisisco i permessi sulla pipe
	if (chmod(pipePath, 0660) < 0) {
		printf(
				"\n[ERROR] (%s) Errore durante l'acquisizione dei permessi sul pipe",
				pipePath);
	} else if (verboseMode == 1) {
		printf(
				"\n[LOG] (%s) Acquisiti permessi per la sessione corrente (0660)",
				pipePath);
		fflush(stdout);
	}
}

/* Aggiunge un client nella lista */
void addClientInList(Client **head, pid_t pid, char* path) {
	if ((*head) == NULL) {
		(*head) = malloc(sizeof(Client));
		(*head)->next = NULL;
		(*head)->pid = pid;
		// apertura in scrittura, bloccante perche' il client dovrebbe già essere in attesa lato lettura
		(*head)->pipe = open(path, O_WRONLY);
	} else {
		Client *last = getLastClient((*head));
		last->next = malloc(sizeof(Client));
		last->next->next = NULL;
		last->next->pid = pid;
		// apertura in scrittura, bloccante perche' il client dovrebbe già essere in attesa lato lettura
		last->next->pipe = open(path, O_WRONLY);
	}
}

