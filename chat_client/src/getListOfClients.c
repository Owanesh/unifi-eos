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
int messageListConfirmed();
void printList(char* list);
/*
 * NOTA DI PROGETTAZIONE: la stringa passata al client sarà del tipo
 * LIST <lunghezza in byte> <stringa>
 * dove <lunghezza in byte> indica la lunghezza della lista da leggere
 */
void getListOfClients() {
	sendRequestToServer();
	char *list = allocationString();
	if (list != NULL) {
		int n;
		do { // Legge fino a '\0' o EOF
			n = read(fdClientPipe, list, 1);
		} while (n > 0 && *list++ != '\0');
		printList(list);
		free(list);
	}
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
	if (messageListConfirmed()) {
		char *str = malloc(sizeof(char) * 10); //MAX 10 cifre dovrebbero sempre bastare
		char *start = str;
		int n;
		do { // Legge il numero che indica quanti byte allocare per la lista
			n = read(fdClientPipe, str, 1);
		} while (n > 0 && *str++ != ' ');
		*str = '\0';
		str = start;
		long dimension = strtol(start, NULL, 10);
		free(str);
		return malloc(sizeof(char) * dimension);
	} else {
		return NULL;
	}
}

int messageListConfirmed() {
	char *str = malloc(sizeof(char) * 20);
	char *start = str;
	int result, n;
	do { //prima devo leggere la parola chiave LIST
		n = read(fdClientPipe, str, 1);
	} while (n > 0 && *str++ != ' ');
	*str = '\0';
	str = start;
	if (strncmp(str, "LIST", 4) != 0) {
		printf("Mi aspettavo LIST e ho trovato %s", str);
		result = 0;
	} else {
		result = 1;
	}
	free(str);
	return result;
}
void printList(char* list) {
	//SOLO PER PROVA
	printf("%s\n", list);
}
