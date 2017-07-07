#include "header/utilities.h"
#include "header/connect.h"
#include "header/main_client.h"
#include "header/handler_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// opzioni del menù principale
const char* options[] =
		{ "(1) Connessione al server", "(2) Elenco dei client",
				"(3) Invia messaggio", "(4) Disconnessione dal server",
				"(5) Esci", NULL };

int connected = 0;
/* Controlla la scelta dell'utente ed invoca le funzioni opportune */
void switchOptions(int value) {
	switch (value) {
	case 1:
		if (connect()) {
			connected = 1;
		} else {
			printf("Connessione non riuscita.\n");
		}
		break;
	case 2:
		if (connected)
			getListOfClients();
		else
			printf("Non sei connesso.\n");
		break;
	case 3:
		if (connected)
			sendMessage();
		else
			printf("Non sei connesso.\n");
		break;
	case 4:
		if (connected)
			disconnect();
		else
			printf("Non sei connesso.\n");
		break;
	case 5:
		terminate();
		break;
	}
}

int main(int argc, const char **argv) {
	//^C richiama l'handler di disconnessione prima di terminare il programma
	signal(SIGINT, handler_termination);
	int optionsAllowed[] = { 1, 5 };
	int value;
	do {
		value = selectOption("Selezionare un'opzione del menu': ",
				optionsAllowed,
				NULL, 0);
		switchOptions(value);
	} while (value != 5);
	printf("\nProgramma terminato.");
	exit(EXIT_SUCCESS);
}
