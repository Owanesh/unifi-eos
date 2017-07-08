#include "header/main_client.h"
#include "header/connect.h"
#include "header/getListOfClients.h"
#include "header/sendMessage.h"
#include "header/handler_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "header/utilities.h"

// opzioni del menù principale
const char* options[] = { "(1) Connessione al server", "(2) Elenco dei client",
		"(3) Invia messaggio", "(4) Visualizza i nuovi messaggi",
		"(5) Disconnessione dal server", "(6) Esci", NULL };

int connected = 0;
/* Controlla la scelta dell'utente ed invoca le funzioni opportune */
void switchOptions(int value) {
	switch (value) {
	case 1:
		if (connect()) {
			countMessages = 0;
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
			seeNewMessages();
		else
			printf("Non sei connesso.\n");
		break;
	case 5:
		if (connected)
			disconnect();
		else
			printf("Non sei connesso.\n");
		break;
	case 6:
		terminate();
		break;
	}
}

int main(int argc, const char **argv) {
	//^C richiama l'handler di disconnessione prima di terminare il programma
	signal(SIGINT, handler_termination);
	//routine di gestione di un nuovo messaggio riceuto
	signal(SIGUSR1, handler_new_message);
	//ruotine di gestione "destinatario non trovato"
	signal(SIGUSR2, handler_dest_not_found);
	int optionsAllowed[] = { 1, 6 };
	int value;
	do {
		char *footer = NULL;
		sprintf(footer, "Hai %d nuovi messaggi", countMessages);
		printMenu(options, "Chat C", footer, false, true, 50);
		value = selectOption("Selezionare un'opzione del menu': ",
				optionsAllowed,
				NULL, 0);
		switchOptions(value);
	} while (value != 6);
	printf("\nProgramma terminato.");
	exit(EXIT_SUCCESS);
}