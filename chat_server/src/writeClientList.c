#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "header/client.h"
#include "header/writeClientList.h"
#include "header/server.h"

char* buildMessage(Client* head, pid_t pid);
int countClients(Client* head);

/* Scorre la lista dei client individuando tutti i pid dei client connessi.
 * Ottiene la stringa rappresentante la lista e la scrive sulla pipe corretta.*/
void writeClientList(Client *head, char* cmd) {
	if (head == NULL) {
		printf("\n *** NESSUN UTENTE CONNESSO ***");
	} else {
		pid_t pid;
		getPidFromCmd(cmd, &pid); // acquisisco il pid del richiedente
		char* list = buildMessage(head, pid);
		int fd;
		fd = getPipeByPid(pid, head); // trovo il riferimento alla pipe
		if (fd != 0)
			write(fd, list, strlen(list) + 1);
		free(list);
	}
}

char* buildMessage(Client* head, pid_t pid) {
	int count = countClients(head);
	/* alloco 20 caratteri per ogni pid (dovrebbero sempre bastare)
	 + 50 caratteri per il messaggio iniziale*/
	char* str = malloc(sizeof(char) * ((count * 20) + 50));
	if (str == NULL)
		exit(EXIT_FAILURE);
	if (count == 1) {
		sprintf(str, "Sei l'unico utente connesso:\nil tuo id e' %d.", pid);
	} else {
		sprintf(str, "Sono presenti %d clients:\n", count);
		printf("\n*** LISTA UTENTI CONNESSI ***");
		do {
			printf("\n %d", head->pid);
			char temp[40];
			if (head->pid == pid)
				sprintf(temp, "%d (il tuo id)\n", head->pid); // il tuo pid
			else
				sprintf(temp, "%d\n", head->pid); // converto il pid in stringa
			strcat(str, temp);
			head = head->next;
		} while (head != NULL);
	}
	return str;
}

/*
 * Conta il numero di clients connessi (escluso il pid mittente)
 */
int countClients(Client* head) {
	int count = 0;
	do {
		count++;
		head = head->next;
	} while (head != NULL);
	return count;
}
