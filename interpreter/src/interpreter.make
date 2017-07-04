interpreter: main.o parallelExec.o sequentialExec.o handle_sigchld.o readCommand.o utilities.o
	cc -o "interpreter" main.o parallelExec.o sequentialExec.o handle_sigchld.o readCommand.o utilities.o
main.o: main.c header/parallelExec.h header/readCommand.h header/handle_sigchld.h header/sequentialExec.h header/utilities.h
	cc -c main.c
parallelExec.o: parallelExec.c header/parallelExec.h header/readCommand.h header/handle_sigchld.h
	cc -c parallelExec.c
handle_sigchld.o: handle_sigchld.c header/handle_sigchld.h
	cc -c handle_sigchld.c
readCommand.o: readCommand.c header/readCommand.h header/utilities.h
	cc -c readCommand.c
sequentialExec.o: sequentialExec.c header/sequentialExec.h header/readCommand.h
	cc -c sequentialExec.c
utilities.o: utilities.c header/utilities.h
	cc -c utilities.c


