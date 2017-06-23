scheduler: main.o insert.o execute.o delete.o changeScheduling.o modify.o readyQueue.o task.o utilities.o
	cc -o "scheduler" main.o insert.o execute.o delete.o changeScheduling.o modify.o readyQueue.o task.o utilities.o
main.o: main.c header/task.h header/utilities.h header/readyQueue.h header/insert.h header/execute.h header/delete.h header/modify.h header/changeScheduling.h
	cc -c main.c
insert.o: insert.c header/insert.h header/readyQueue.h header/utilities.h
	cc -c insert.c
execute.o: execute.c header/execute.h header/readyQueue.h header/delete.h
	cc -c execute.c
delete.o: delete.c header/delete.h header/readyQueue.h
	cc -c delete.c
changeScheduling.o: changeScheduling.c header/changeScheduling.h header/utilities.h header/readyQueue.h
	cc -c changeScheduling.c
modify.o: modify.c header/modify.h header/utilities.h header/readyQueue.h
	cc -c modify.c
readyQueue.o: readyQueue.c header/readyQueue.h header/task.h
	cc -c readyQueue.c
task.o: task.c header/task.h
	cc -c task.c
utilities.o: utilities.c header/utilities.h
	cc -c utilities.c
