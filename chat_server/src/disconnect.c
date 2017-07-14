#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> /* unlink */
#include "header/client.h"
#include "header/server.h"
#include "header/disconnect.h"

int deleteHead(Client **head, pid_t pid);
int deleteNode(Client **head, pid_t pid);
Client* previousClient(Client **head, pid_t pid);

/*
 * Elimina il client specificato da pid dalla lista.
 */
void disconnect(Client **head, char* cmd) {
	if ((*head) == NULL) {
		printf("\n [ERRORE] Nessun utente connesso");
		return;
	}
	pid_t pid;
	getPidFromCmd(cmd, &pid);
	int fd;
	if ((*head)->pid == pid) {
		//eliminazione nodo iniziale
		fd = deleteHead(head, pid);
	} else {
		//eliminazione nodo intermedio (o finale)
		fd = deleteNode(head, pid);
	}
	// chisura ed eliminazione della pipe del client
	char temp[50];
	getClientPipePath(pid, temp);
	closeConnection(fd, temp);
}

/*
 * Rimuove il Client specificato e ritorna il fd della relativa pipe
 */
int deleteHead(Client **head, pid_t pid) {
	int fd = (*head)->pipe;
	Client* ptrToFree = *head;
	*head = (*head)->next;
	free(ptrToFree);
	return fd;
}

/*
 * Rimuove il Client specificato e ritorna il fd della relativa pipe
 */
int deleteNode(Client **head, pid_t pid) {
	Client *previous = previousClient(head, pid);
	int fd = 0;
	if (previous != NULL) {
		fd = previous->next->pipe;
		Client* ptrToFree = previous->next;
		previous->next = previous->next->next;
		free(ptrToFree);
	}
	return fd;
}

/* Dato il pid, ritorna l'elemento precedente a quello richiesto*/
Client* previousClient(Client **head, pid_t pid) {
	if ((*head) == NULL) {
		return NULL;
	}
	Client *clone = *head;
	do {
		if (clone->next->pid == pid)
			return clone;
		clone = clone->next;
	} while (clone != NULL);
	return NULL;
}

/*Chiude la pipe e la elimina */
void closeConnection(int fd, char* pipePath) {
	close(fd);
	unlink(pipePath);
	printf("\n[SUCCESS] Sessione terminata per %s ", pipePath);
}
