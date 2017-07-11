/*
 * connect.h
 *
 *  Created on: Jul 11, 2017
 *      Author: Owanesh
 */

#ifndef HEADER_CONNECT_H_
#define HEADER_CONNECT_H_

void acceptConnection(Client **head, pid_t pid);
void addClientInList(Client **head, pid_t pid);
bool isAlreadyConnected(Client **head, pid_t pid);
void createPipe(char* pipeName);

#endif /* HEADER_CONNECT_H_ */
