#ifndef HEADER_DELETE_H_
#define HEADER_DELETE_H_

#include "readyQueue.h"

/*
 * Elimina il task specificato, ritorna 1 in caso di successo, altrimenti 0
 */
int deleteById(ReadyQueue **head, unsigned long id);

/*
 * Elimina il task specificato.
 * Ritorna 1 in caso di successo, altrimenti 0
 */
int delete(ReadyQueue **head, ReadyQueue *task);

#endif /* HEADER_DELETE_H_ */
