#include <stdio.h>
#include <stdlib.h>
#include "header/handler_functions.h"
#include "header/main_client.h"
void handler_termination() {
	signal(SIGINT, handler_termination);
}
void handler_new_message() {
	//lettura dalla pipe e inserimento nel buffer messages (definito in main_client.h)
	countMessages++;
	messages = realloc(messages, sizeof(char*) * countMessages);
	messages[countMessages - 1] = malloc(sizeof(char) * MAX_LENGTH_MSG);

	signal(SIGUSR1, handler_new_message);
}

void handler_dest_not_found() {
	signal(SIGUSR2, handler_dest_not_found);
}
