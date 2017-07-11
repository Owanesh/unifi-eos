#include "header/utilities.h"
#include "header/server.h"
#include "header/connect.h"
#include "header/disconnect.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Client *head = NULL; //client list

void switchCommand(char* cmd) {
	if (strcmp(cmd, "LIST") == 0) {
		printf("\n\t List cmd request ");
	} else if (strcmp(cmd, "CONNECT") == 0) {
		printf("\n\t CONNECT cmd request ");
	} else if (strcmp(cmd, "MSG") == 0) {
		printf("\n\t MSG cmd request ");
	} else if (strcmp(cmd, "DISCONNECT") == 0) {
		printf("\n\t DISCONNECT cmd request ");
	} else {
		printf("<%s> Comando non riconosciuto", cmd);
	}
}
int main(int argc, const char **argv) {
	start();
	char str[100];
	readCommand(getServerPipe(), str);
	acceptConnection(&head, 111);
	acceptConnection(&head, 444);
	connectedClientList(head);
	acceptConnection(&head, 111);

}
