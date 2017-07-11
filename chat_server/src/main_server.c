#include "header/utilities.h"
#include "header/server.h"

#include <stdio.h>
#include <stdlib.h>

Client *head = NULL; //client list

int main(int argc, const char **argv) {
	start();
	acceptConnection(&head,111);
	acceptConnection(&head,222);
	acceptConnection(&head,333);
	acceptConnection(&head,444);
	acceptConnection(&head,111);
	connectedClientList(head);




}
