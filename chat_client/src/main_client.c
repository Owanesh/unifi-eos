#include "header/utilities.h"

#include <stdio.h>
#include <stdlib.h>

// opzioni del menù principale
const char* options[] =
		{ "(1) Connessione al server", "(2) Elenco dei client",
				"(3) Invia messaggio", "(4) Disconnessione dal server",
				"(5) Esci", NULL };

/* Controlla la scelta dell'utente ed invoca le funzioni opportune */
void switchOptions(int value) {
	switch (value) {
	case 1:
		connect();
		break;
	case 2:
		getListOfClients();
		break;
	case 3:
		sendMessage();
		break;
	case 4:
		disconnect();
		break;
	case 5:
		terminate();
		break;

	}
}

int main(int argc, const char **argv) {
	int optionsAllowed[] = { 1, 5 };
	int value;
	value = selectOption("Selezionare un'opzione del menu': ", optionsAllowed,
	NULL, 0);
	switchOptions(value);
	printf("\nProgramma terminato.");
	exit(EXIT_SUCCESS);
}
