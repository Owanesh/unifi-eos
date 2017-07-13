#ifndef HEADER_DISCONNECT_H_
#define HEADER_DISCONNECT_H_
#include "client.h"

void disconnect(Client **head, char* cmd);
void closeConnection(int fd, char* pipePath);

#endif /* HEADER_DISCONNECT_H_ */
