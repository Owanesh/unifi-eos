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

void getListOfClients() {
	sendRequestToServer();
	char *str = allocationString();
	int n;
	do { // Legge fino a '\0' o EOF
		n = read(fdClientPipe, str, 1);
	} while (n > 0 && *str++ != '\0');
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
	char *str = malloc(sizeof(char) * 100);
	int n = 0, index = 0;
	do { // Legge il numero che indica quanti byte allocare per la lista
		n = read(fdClientPipe, str, 1);
		index++;
	} while (*str++ != ' ');
}
