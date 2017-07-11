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

/* Cancelliamo la testa della lista */
void deleteHead(Client **head, pid_t pid) {
 	*head = (*head)->next;
 }

/* Dato il pid, ritorna l'elemento precedente a quello richiesto,
 * utile per eliminare un client dalla lista*/
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

/*Chiude la pipe e ne elimina il file relativo*/
void closeConnection(int closePipe, char* pipeName) {
	close(closePipe);
	unlink(pipeName);
	printf("\n[SUCCESS] Sessione terminata per %s ", pipeName);
}
