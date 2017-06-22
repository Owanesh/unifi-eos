/*
 * changeScheduling.h
 *
 *  Created on: 20 giu 2017
 *      Author: matteomauro
 */

#ifndef HEADER_CHANGESCHEDULING_H_
#define HEADER_CHANGESCHEDULING_H_
#define POLICY_PRIORITY 0
#define POLICY_EXEC_CYCLES 1

#include "readyQueue.h"

// policySheduling = 0 -> PRIORITA (DEFAULT)
// policySheduling = 1 -> ESECUZIONI RIMANENTI
// defined in changeScheduling.c in order to be available for the other modules
extern int policyScheduling;

void changeScheduling(ReadyQueue *head);
void bubbleSort(ReadyQueue **head);

#endif /* HEADER_CHANGESCHEDULING_H_ */
