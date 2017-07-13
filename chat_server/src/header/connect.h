#ifndef HEADER_CONNECT_H_
#define HEADER_CONNECT_H_
#include "client.h"

void acceptConnection(Client **head, char* cmd);
void createPipe(char* pipeName);

#endif /* HEADER_CONNECT_H_ */
