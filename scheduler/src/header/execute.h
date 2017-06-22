/*
 * execute.h
 *
 *  Created on: 20 giu 2017
 *      Author: matteomauro
 */

#ifndef HEADER_EXECUTE_H_
#define HEADER_EXECUTE_H_

#include "readyQueue.h"

void execute(ReadyQueue *head);
void executeById(ReadyQueue *head, unsigned long id);

#endif /* HEADER_EXECUTE_H_ */
