#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header/handler_functions.h"
#include "header/main_client.h"

void handler_termination() {
	signal(SIGINT, handler_termination);
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
	signal(SIGUSR1, handler_new_message); //riattivo l'handler
}

void handler_dest_not_found() {
	signal(SIGUSR2, handler_dest_not_found);
}
