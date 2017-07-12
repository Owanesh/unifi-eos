#ifndef HEADER_CLIENT_H_
#define HEADER_CLIENT_H_
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


typedef struct Client {
	pid_t pid;
	struct Client *next;
    int pipe;
} Client;



#endif /* HEADER_CLIENT_H_ */
