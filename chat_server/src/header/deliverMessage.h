#ifndef HEADER_DELIVERMESSAGE_H_
#define HEADER_DELIVERMESSAGE_H_
#include "client.h"
#define MAX_LENGTH_MSG 4096

void deliverMessage(Client* head, char* cmd);
#endif /* HEADER_DELIVERMESSAGE_H_ */
