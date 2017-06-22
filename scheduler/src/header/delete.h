#ifndef HEADER_DELETE_H_
#define HEADER_DELETE_H_

#include "readyQueue.h"

/*
 * Deletes the task specified by id, returns 1 in case of success, otherwise 0 (i.e. taks not found)
 */
int deleteById(ReadyQueue **head, unsigned long id);

/*
 * Deletes the task passed as argument (head might be changed so it's necessary to the function)
 * Returns 1 in case of success, otherwise 0 (head is empty)
 */
int delete(ReadyQueue **head, ReadyQueue *task);

#endif /* HEADER_DELETE_H_ */
