#include "header/utilities.h"
#include "header/server.h"

#include <stdio.h>
#include <stdlib.h>

Client *head = NULL; //client list

int main(int argc, const char **argv) {
	start();
	acceptConnection(head,1223);
}
