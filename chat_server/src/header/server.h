#ifndef HEADER_SERVER_H_
#define HEADER_SERVER_H_
#include <fcntl.h>
#include "client.h"

/* Basic server command*/
void start();
void stop();

char** getListOfUser(int pidRequest);
void sendMessage(int pidFrom, int pidTo);

char* getClientPipeName(pid_t pid);

int openReadPipe(char* pipeName);

void readCommand(char *str);
void getFirstField(char keyword[20], char* cmd);

int getServerPipe();
char* pipeFullPath(char* name);

Client* getLastClient(Client *head);
void connectedClientList(Client *head);
#endif /* HEADER_SERVER_H_ */
