#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "header/main_client.h"
#include "header/getListOfClients.h"
void sendRequestToServer();
void printList(char* list);

void getListOfClients() {
	//dimensione iniziale della lista, se si rivelera' insufficiente verra' riallocata
	int dim = 50;
	sendRequestToServer();
	char *list = malloc(sizeof(char) * dim);
	if (list != NULL) {
		int n, count = 0;
		do { // Legge fino a '\0' o EOF
			n = read(fdClientPipe, list, 1);
			if (n != 0) {
				count++;
				if (count == dim) {
					//rialloco il doppio della dimensione precedente
					list = realloc(list, sizeof(char) * (dim * 2));
					dim *= 2;
					list += (count - 1); //riposiziono il puntatore
				}
			}
		} while (n > 0 && *list++ != '\0');
		printList(list);
		free(list);
	}
}

/*
 * Invia il messaggio "LIST <pid>".
 */
void sendRequestToServer() {
	char msg[50];
	//richiesta-> "LIST <pid>"
	sprintf(msg, "%s %d", "LIST", getpid());
	int msgLength = strlen(msg) + 1;
	write(fdServerPipe, msg, msgLength);
}

void printList(char* list) {
	//SOLO PER PROVA
	printf("Lista dei client connessi:\n%s\n", list);
}
