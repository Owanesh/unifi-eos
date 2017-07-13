#ifndef HEADER_SERVER_H_
#define HEADER_SERVER_H_
#include "client.h"

// file descriptor del server
extern int server_pipe;

void start();
void stop();
void getClientPipePath(pid_t pid, char* bufferPath);
int readCommand(char **str);
void getFirstField(char keyword[20], char* cmd);
void getPidFromCmd(char* cmd, pid_t* pid);
int getPipeByPid(pid_t pid, Client* head);
Client* getLastClient(Client *head);

#endif /* HEADER_SERVER_H_ */
