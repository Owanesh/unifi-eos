#include "header/utilities.h"
#include "header/server.h"
#include "header/connect.h"
#include "header/disconnect.h"
#include "header/writeClientList.h"
#include "header/deliverMessage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// puntatore alla testa della lista dei client
Client *head = NULL;
//definizione delle variabile extern dichiarate in main_client.h
int server_pipe = 0;
// buffer per ogni comando letto da server_pipe
char* command = NULL;

void switchCommand(char* cmd);
void handler_termination();

int main(void) {
	start();
	signal(SIGINT, handler_termination);
	while (1) {
		readCommand(command);
		switchCommand(command);
	}
}

void switchCommand(char* cmd) {
	char keyword[20];
	getFirstField(keyword, cmd);
	if (strcmp(keyword, "LIST") == 0) {
		// "LIST <pid>"
		printf("\n\t LIST cmd request ");
		writeClientList(head, cmd);

	} else if (strcmp(keyword, "CONNECT") == 0) {
		// "CONNECT <pid>"
		printf("\n\t CONNECT cmd request ");
		acceptConnection(&head, cmd);

	} else if (strcmp(keyword, "MSG") == 0) {
		// "MSG <pid_destinatari> $<pid_mittente> <messaggio>"
		printf("\n\t MSG cmd request ");
		deliverMessage(head, cmd);

	} else if (strcmp(keyword, "DISCONNECT") == 0) {
		// "DISCONNECT <pid>"
		printf("\n\t DISCONNECT cmd request ");
		disconnect(&head, cmd);

	} else {
		printf("<%s> \nComando non riconosciuto", cmd);
	}
}

void handler_termination() {
	/*
	 * 1) Libera la memoria di ogni nodo della lista
	 * 2) Chiude ed elimina la connessione con server_pipe
	 * 3) libera command
	 */
	Client* ptr;
	while (head != NULL) {
		ptr = head;
		head = head->next;
		free(ptr);
	}
	close(server_pipe);
	unlink("server_pipe");
	free(command);
	printf("\nIl server e' terminato con successo.");
	exit(EXIT_SUCCESS);
}
