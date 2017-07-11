#include <stdio.h>
#include <stdlib.h>
#include "header/utilities.h"
#include "header/server.h"
#include <sys/stat.h>           /* For S_IFIFO */
#include <fcntl.h>
#include <unistd.h> /* unlink */
#include <string.h>

int log_enabled = 1;

int server_pipe;
char* server_pipe_name = "server_pipe";
char* defaultpath = "../";

Client* getLastClient(Client *head);

void start() {
	openPipe(server_pipe_name);
}

void stop() {
	closeConnection(server_pipe, server_pipe_name);
}

void closeConnection(int closePipe, char* pipeName) {
	close(closePipe);
	unlink(pipeName);
	printf("\n[SUCCESS] Sessione terminata per %s ", pipeName);
}

int openPipe(char* pipeName) {
	int openedPipe;
	char completePipeName[53];
	strcpy(completePipeName, defaultpath);
	strcat(completePipeName, pipeName);
	//rimuovo la vecchia sessione del server
	if (unlink(completePipeName) == -1) {
		printf(
				"\n[ERROR] (%s) Errore durante la rimozione della vecchia sessione",
				pipeName);
	} else if (log_enabled == 1) {
		printf("\n[LOG] (%s) Rimossa sessione precedente", pipeName);
	}
	//creo la nuova pipe
	if (mknod(completePipeName, S_IFIFO, 0) < 0) {
		printf("\n[ERROR] (%s) Errore durante la generazione del pipe",
				pipeName);
	} else if (log_enabled == 1) {
		printf("\n[LOG] (%s) Generata nuova sessione", pipeName);
	}
	//acquisisco i permessi sulla pipe
	if (chmod(completePipeName, 0660) < 0) {
		printf(
				"\n[ERROR] (%s) Errore durante l'acquisizione dei permessi sul pipe",
				pipeName);
	} else if (log_enabled == 1) {
		printf(
				"\n[LOG] (%s) Acquisiti permessi per la sessione corrente (0660)",
				pipeName);
	}
	//apro la pipe
	openedPipe = open(completePipeName, O_RDONLY | O_NONBLOCK); //salvo la pipe per la chiusura
	if (openedPipe == -1) {
		printf("\n[ERROR] (%s) Pipe creata ma inutilizzabile", pipeName);
	} else if (log_enabled == 1) {
		printf("\n[LOG] (%s) La pipe è pronta!", pipeName);
	}

	//ritorno il "puntatore" alla pipe
	return openedPipe;
}

/* return client pipe name */
char* clientPname(pid_t pid) {
	static char pipePath[50];
	char base_string[] = "_client_pipe";
	sprintf(pipePath, "%d%s", pid, base_string);
	return pipePath;
}

/* True: Pid gia presente nella lista
 * False: Pid non presente nella lista
 */
bool isAlreadyConnected(Client **head, pid_t pid) {
	if ((*head) == NULL) {
		return false;
	} else {
		while ((*head)->next != NULL) {
			if ((*head)->pid == pid) {
				return true;
			}
		}
	}
	return false;
}

void addClientInList(Client **head, pid_t pid) {
	if ((*head) == NULL) {
		(*head) = malloc(sizeof(Client));
		(*head)->next = NULL;
		(*head)->pid = pid;
	} else {
		Client *last = getLastClient((*head));
		last->next = malloc(sizeof(Client));
		last->next->next = NULL;
		last->next->pid = pid;
	}
}

void acceptConnection(Client **head, pid_t pid) {
	if (!isAlreadyConnected(head, pid)) {
		if (log_enabled == 1)
			printf("\n[LOG] Request from %d accepted", pid);
		 openPipe(clientPname(pid));
		addClientInList(head, pid);
	} else if (log_enabled == 1) {
		printf("\n[WARNING] %d is already connected ", pid);
	}
}

void connectedClientList(Client **head) {
	if ((*head) == NULL) {
		if (log_enabled == 1) {
			printf("\n[WARNING] Empty List");
		}
		return;
	} else {
		Client *cloneHead = (*head);
		do {
			printf("\n %d", (cloneHead)->pid);
			(cloneHead) = (cloneHead)->next;
		} while ((cloneHead) != NULL);
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
