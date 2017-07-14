#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header/main_client.h"
#include "header/handler_functions.h"
#include "header/disconnect.h"

void handler_termination() {
	// prima di uscire e' necessario avvisare della propria disconnessione
	disconnect();
	exit(EXIT_SUCCESS);
}

void handler_new_message() {
	//lettura dalla pipe e inserimento nel buffer messages (dichiarato in main_client.h)
	countMessages++;
	//rialloco countMessages puntatori
	messages = realloc(messages, sizeof(char*) * countMessages);
	if (messages == NULL)
		exit(EXIT_FAILURE);
	//alloco lo spazio per il nuovo messaggio
	messages[countMessages - 1] = malloc(sizeof(char) * MAX_LENGTH_MSG);
	if (messages[countMessages - 1] == NULL)
		exit(EXIT_FAILURE);
	char* ptr = messages[countMessages - 1]; //alias
	int n;
	do { // Legge fino a '\0' o EOF
		n = read(fdClientPipe, ptr, 1);
	} while (n > 0 && *ptr++ != '\0');
	printf("\n[NOTA] E' disponibile un nuovo messaggio (aggiorna il menu' per vedere quanti ne sono disponibili).\n");
	fflush(stdout);
	signal(SIGUSR1, handler_new_message); //riattivo l'handler
}

void handler_dest_not_found() {
	printf(
			"\n[NOTA] Il messaggio non e' stato recapitato: uno o piu' destinatari inesistenti.\n");
	fflush(stdout);
	signal(SIGUSR2, handler_dest_not_found); //riattivo l'handler
}
