#ifndef HEADER_TASK_H_
#define HEADER_TASK_H_

typedef struct Task {
	unsigned long id;
	char name[9];
	unsigned char priority;
	unsigned char exec_cycles;
} Task;
typedef unsigned char byte;

/*
 * Funzione setter di un task comprendente tutti i possibili parametri.
 * Restituisce 0 se i parametri non sono validi, altrimenti un numero !=0
 */
int setTask(Task* t, char* name, byte priority, byte exec_cycles);

#endif /* HEADER_TASK_H_ */
