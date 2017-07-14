#include "header/deliverMessage.h"
#include "header/client.h"
#include "header/server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int extractFields(pid_t*** receivers, pid_t* sender, char** message, char* cmd);
char** parseCommand(char *cmd, int* num_of_fields);
int countFields(char* cmd, const char token_delimiter);
void str_split(char* cmd, const char token_delimiter, char** fields);
int checkReceivers(Client* head, pid_t** receivers, int countReceivers,
		char* message);

int getSenderPipe(pid_t sender, Client* head);

void deliverMessage(Client* head, char* cmd) {
	/*
	 * 1) Estrarre tutti i relativi campi da cmd
	 * 		- pid destinatari
	 * 		- pid mittente
	 * 		- messaggio
	 * 2) Per ogni pid destinatario, verificare se esiste
	 * 		- in caso affermativo si scrive il messaggio nella relativa
	 * 		  pipe e si segnala SIGUSR1 ("nuovo emssaggio")
	 * 		- altrimenti si invia un signal SIGUSR2 al pid mittente ("dest inesistente")
	 * 3)  Liberare la memoria allocata dinamicamente
	 */
	pid_t** receivers = NULL;
	pid_t sender;
	char* message = NULL;
	int countReceivers = extractFields(&receivers, &sender, &message, cmd); //1)
	int countExistings = checkReceivers(head, receivers, countReceivers,
			message); //2)
	printf("\nSono stati inviati %d messaggi.\n", countExistings);
	if (countExistings < countReceivers) // non tutti i destinatari erano corretti
		kill(sender, SIGUSR2);

	//3)
	int i = 0;
	for (; i < countReceivers; i++) {
		free(receivers[i]);
	}
	free(receivers);
	free(message);
}

int extractFields(pid_t*** receivers, pid_t* sender, char** message, char* cmd) {
	// separato tutti i campi riga per riga
	int num_of_fields;
	char** fields = parseCommand(cmd, &num_of_fields);
	// conto quanti receivers ci sono (il mittente inizia con '$')
	int count = 1;
	while (*(fields + count)[0] != '$')
		count++;
	// alloco lo spazio per contenerli tutti
	count--; //tolgo il MSG iniziale
	*receivers = malloc(sizeof(pid_t*) * count);
	// acquisisco i pid dei receivers
	int i = 1;
	for (; i <= count; i++) {
		*(*receivers + (i - 1)) = malloc(sizeof(pid_t));
		*(*(*receivers + (i - 1))) = strtol(*(fields + i), NULL, 10);
	}
	// acquisisco il mittente
	*sender = strtol((*(fields + i)) + sizeof(char), NULL, 10); //+sizeof(char) per oltrepassare il'$' iniziale
	// acquisisco il messaggio
	i++;
	*message = malloc(sizeof(char) * (strlen(*(fields + i)) + 1)); //+1 per '\0'
	strcpy(*message, *(fields + i));
	for (i = 0; i < num_of_fields; i++) {
		free(fields[i]);
	}
	free(fields);
	return count;
}

/*
 * Restituisce una array di stringhe, il numero di righe è pari al numero dei campi
 * del comando passato piu' una riga NULL finale (salvato in num_of_fields)
 */
char** parseCommand(char *cmd, int* num_of_fields) {
	*num_of_fields = countFields(cmd, ' ');
	char** fields = malloc(sizeof(char*) * (*num_of_fields));
	str_split(cmd, ' ', fields);
	return fields;
}

/*
 * Determina il numero di campi di cmd piu' una riga NULL
 */
int countFields(char* cmd, const char token_delimiter) {
	int token_counter = 0;

	/* Conteggio di quanti token troviamo scorrendo la stringa  */
	while (*cmd) {
		if (token_delimiter == *cmd) {
			token_counter++;
		}
		cmd++;
	}
	//+2 per il MSG e per il NULL finale
	token_counter += 2;
	return token_counter;
}

/*
 * Associa ad ogni riga di fields un campo del comando
 */
void str_split(char* cmd, const char token_delimiter, char** fields) {
	int id_tok = 0;
	char delim[] = { token_delimiter, '\0' };
	char* token = strtok(cmd, delim);
	/* Preso il token successivo (strtok), controllo se e' valido*/
	while (token != NULL) {
		fields[id_tok] = strdup(token);
		token = strtok(0, delim);
		id_tok++;
	}
	fields[id_tok] = NULL;
}

int checkReceivers(Client* head, pid_t** receivers, int countReceivers,
		char* message) {
	int length = strlen(message) + 1;
	int i = 0, countExistings = 0;
	Client* node;
	for (; i < countReceivers; i++) {
		int j = 0, found = 0;
		node = head; //ripristino la partenza
		for (; j < countReceivers && !found && node != NULL; j++) {
			if (node->pid == *(receivers[j])) {
				write(node->pipe, message, length);
				found = 1;
				countExistings++;
				kill(node->pid, SIGUSR1);
			}
			node = node->next;
		}
	}
	return countExistings;
}

int getSenderPipe(pid_t sender, Client* head) {
	int found = 0, fd;
	do {
		if (head->pid == sender) {
			found = 1;
			fd = head->pipe;
		}
		head = head->next;
	} while (head != NULL && !found);
	return fd;
}
