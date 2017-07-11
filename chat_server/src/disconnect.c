#include <stdlib.h>
#include <stdio.h>
#include "header/client.h"
#include <fcntl.h>
#include <unistd.h> /* unlink */
#include <string.h>

void removeCase(Client **head, pid_t pid);
void deleteHead(Client **head, pid_t pid);
Client* previousClient(Client **head, pid_t pid);
void deleteClient(Client *previous);
/*
 * Elimina il task specificato.
 * Ritorna 1 in caso di successo, altrimenti 0
 */
void delete(Client **head, pid_t pid) {
	if ((*head) == NULL) {
		printf("\n [ERRORE] Nessun utente connesso");
		return;
	}
	removeCase(head, pid);
}

void removeCase(Client **head, pid_t pid) {
	if ((*head)->pid == pid) {
		deleteHead(head, pid);
	}
	Client *prev = previousClient(head, pid);
	if (prev != NULL) {
		deleteClient(prev);
	}
}

void deleteClient(Client *previous) {
	previous->next = previous->next->next;
}

void deleteHead(Client **head, pid_t pid) {
 	*head = (*head)->next;
 }

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


void closeConnection(int closePipe, char* pipeName) {
	close(closePipe);
	unlink(pipeName);
	printf("\n[SUCCESS] Sessione terminata per %s ", pipeName);
}
