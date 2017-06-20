typedef struct Task {
	unsigned long id;
	char name[9];
	unsigned char priority;
	unsigned char exec_cycles;
} Task;
typedef unsigned char byte;

/*
 *setTask necessita un puntatore ad un task, altrimenti le modifiche sarebbero locali alla funzione
 */
int setTask(Task* t, char* name, byte priority, byte exec_cycles);

void getTaskDescription(Task* t, char* buffer);
