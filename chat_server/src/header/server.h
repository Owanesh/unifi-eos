#ifndef HEADER_SERVER_H_
#define HEADER_SERVER_H_
#include <fcntl.h>
#include "client.h"

/* Basic server command*/
void start();
void stop();

char** getListOfUser(int pidRequest);
void sendMessage(int pidFrom, int pidTo);

void closeConnection(int closePipe, char* pipeName);
char* clientPname(pid_t pid);

int createPipe(char* pipeName);
int openPipe(char* pipeName);

void acceptConnection(Client **head, pid_t pid);
void connectedClientList(Client *head);
int readCommand (int fd, char *str);

int getServerPipe();
char* pipeFullPath(char* name);

Client* getLastClient(Client *head);

#endif /* HEADER_SERVER_H_ */
