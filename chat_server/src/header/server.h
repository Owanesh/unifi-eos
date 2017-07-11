#ifndef HEADER_SERVER_H_
#define HEADER_SERVER_H_
#include <fcntl.h>

typedef struct Client {
	pid_t pid;
	struct Client *next;
} Client ;

/* Basic server command*/
void start();
void stop();

char** getListOfUser(int pidRequest);
void sendMessage(int pidFrom, int pidTo);
void closeConnection(int closePipe, char* pipeName);
char* clientPname(pid_t pid);
int openPipe(char* pipeName);
void acceptConnection(Client **head, pid_t pid);
void connectedClientList(Client **head);
#endif /* HEADER_SERVER_H_ */
