#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "header/main_client.h"
#include "header/getListOfClients.h"
void sendRequestToServer();

void getListOfClients() {
	/*
	 * 1) Invia richiesta al server
	 * 2) Alloca lo spazio per salvare la lista
	 * 3) Legge un carattere alla volta da fdClientPipe
	 * 4) se necessario rialloca più spazio
	 * 5) stampa la lista su stdout
	 * 6) libera lo spazio occupato
	 */
	//dimensione iniziale della lista, se si rivelera' insufficiente verra' riallocata
	int dim = 64;
	sendRequestToServer();
	char *list = malloc(sizeof(char) * dim);
	char* start;
	if (list != NULL) {
		start = list;
		int n, count = 0;
		do { // Legge fino a '\0' o EOF
			n = read(fdClientPipe, list, 1);
			if (n != 0) {
				count++;
				if (count == dim) {
					//rialloco il doppio della dimensione precedente
					list = realloc(list, sizeof(char) * (dim * 2));
					start = list;
					dim *= 2;
					list += (count - 1); //riposiziono il puntatore
				}
			}
		} while (n > 0 && *list++ != '\0');
		printf("%s", start);
		free(start);
	}
}

/*
 * Invia il messaggio "LIST <pid>".
 */
void sendRequestToServer() {
	char msg[50];
	//richiesta-> "LIST <pid>"
	sprintf(msg, "%s %d", "LIST", getpid());
	int msgLength = strlen(msg) + 1; //+1 per '\0'
	write(fdServerPipe, msg, msgLength);
}

