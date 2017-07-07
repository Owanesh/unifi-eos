#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "header/main_client.h"
#include "header/getListOfClients.h"
void sendRequestToServer();
char *allocationString();
/*
 * NOTA DI PROGETTAZIONE: la stringa passata al client sarà del tipo
 * LIST <lunghezza in byte> <stringa>
 * dove <lunghezza in byte> indica la lunghezza della lista da leggere
 */
void getListOfClients() {
	sendRequestToServer();
	char *list = allocationString();
	int n;
	do { // Legge fino a '\0' o EOF
		n = read(fdClientPipe, list, 1);
	} while (n > 0 && *list++ != '\0');
	//stampa *list
	//printList(list);
}

/*
 * Invia il messaggio "LIST <pid>".
 */
void sendRequestToServer() {
	char msg[15];
	//richiesta-> "LIST <pid>"
	sprintf(msg, "%s %d", "LIST", getpid());
	int msgLength = strlen(msg);
	write(fdServerPipe, msg, msgLength);
}

char *allocationString() {
	// str conterrà il numero di byte da allocare per la lista
	char *str = malloc(sizeof(char) * 10);
	char *start = str;
	do { // Legge il numero che indica quanti byte allocare per la lista
		read(fdClientPipe, str, 1);
	} while (*str++ != ' ');
	long dimension = strtol(start, NULL, 10);
	return malloc(sizeof(char) * dimension);
}
