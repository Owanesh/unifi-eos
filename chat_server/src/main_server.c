#include "header/utilities.h"
#include "header/server.h"

#include <stdio.h>
#include <stdlib.h>

Client *head = NULL; //client list

int main(int argc, const char **argv) {
	start();
	acceptConnection(&head,1223);
	acceptConnection(&head,777);
	connectedClientList(&head);
	acceptConnection(&head,444);

	connectedClientList(&head);

}
