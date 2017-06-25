#ifndef HEADER_CHANGESCHEDULING_H_
#define HEADER_CHANGESCHEDULING_H_
#define POLICY_PRIORITY 0
#define POLICY_EXEC_CYCLES 1

#include "readyQueue.h"

/* policySheduling = 0 -> PRIORITA (DEFAULT)
 * policySheduling = 1 -> ESECUZIONI RIMANENTI
 */
extern int policyScheduling;

void changeScheduling();
void bubbleSort(ReadyQueue **head);

#endif /* HEADER_CHANGESCHEDULING_H_ */
