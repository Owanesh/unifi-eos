#include "header/utilities.h"
#include "header/server.h"
#include "header/connect.h"
#include "header/disconnect.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Client *head = NULL; //client list

void switchCommand(char* cmd) {
	char keyword[20];
	getFirstField(keyword, cmd);
	if (strcmp(keyword, "LIST") == 0) {
		printf("\n\t LIST cmd request ");
	} else if (strcmp(keyword, "CONNECT") == 0) {
		printf("\n\t CONNECT cmd request ");

	} else if (strcmp(keyword, "MSG") == 0) {
		printf("\n\t MSG cmd request ");

	} else if (strcmp(keyword, "DISCONNECT") == 0) {
		printf("\n\t DISCONNECT cmd request ");
	} else {

		printf("<%s> \nComando non riconosciuto", cmd);
	}
}

int main(int argc, const char **argv) {
	start();
	char* command = NULL;
	while (1) {
		readCommand(command);
		switchCommand(command);
	}

	acceptConnection(&head, 111);
	acceptConnection(&head, 444);
	connectedClientList(head);
	acceptConnection(&head, 111);

}
