/*
 * disconnect.h
 *
 *  Created on: Jul 11, 2017
 *      Author: Owanesh
 */

#ifndef HEADER_DISCONNECT_H_
#define HEADER_DISCONNECT_H_
#include <fcntl.h>

void delete(Client **head,pid_t pid);
void closeConnection(int closePipe, char* pipeName);

#endif /* HEADER_DISCONNECT_H_ */
