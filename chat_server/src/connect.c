#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>           /* For S_IFIFO */
#include <unistd.h> /* unlink */

#include "header/client.h"
#include "header/utilities.h"
#include "header/server.h"
/* Crea una pipe, a partire dal nome, e ne acquisice i permessi (0660)
 * */


void createPipe(char* pipeName) {
 	char* completePipeName = pipeFullPath(pipeName);
	//rimuovo la vecchia sessione del server
	if (unlink(completePipeName) == -1) {
		printf(
				"\n[ERROR] (%s) Errore durante la rimozione della vecchia sessione",
				pipeName);
	} else if (verboseMode == 1) {
		printf("\n[LOG] (%s) Rimossa sessione precedente", pipeName);
		fflush(stdout);
	}
	//creo la nuova pipe
	if (mknod(completePipeName, S_IFIFO, 0) < 0) {
		printf("\n[ERROR] (%s) Errore durante la generazione del pipe",
				pipeName);
	} else if (verboseMode == 1) {
		printf("\n[LOG] (%s) Generata nuova sessione", pipeName);
		fflush(stdout);

	}
	//acquisisco i permessi sulla pipe
	if (chmod(completePipeName, 0660) < 0) {
		printf(
				"\n[ERROR] (%s) Errore durante l'acquisizione dei permessi sul pipe",
				pipeName);
	} else if (verboseMode == 1) {
		printf(
				"\n[LOG] (%s) Acquisiti permessi per la sessione corrente (0660)",
				pipeName);
		fflush(stdout);
	}

}


 /* True: Pid gia presente nella lista
 * False: Pid non presente nella lista
 */
bool isAlreadyConnected(Client **head, pid_t pid) {
	if ((*head) == NULL) {
		return false;
	} else {
		Client *chead = (*head);
		do {
			if (chead->pid == pid) {
				return true;
			}
			chead = chead->next;
		} while (chead != NULL);
	}
	return false;
}

/* Aggiunge un client nella lista */
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
		if (verboseMode == 1) {
			printf("\n[LOG] Request from %d accepted", pid);
			fflush(stdout);
		}
		//fork
		createPipe(clientPname(pid));
		addClientInList(head, pid);
	} else if (verboseMode == 1) {
		printf("\n[WARNING] %d is already connected ", pid);
		fflush(stdout);
	}
}
