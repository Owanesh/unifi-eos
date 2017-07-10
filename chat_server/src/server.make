server: main_server.o server.o utilities.o
	cc -o "server" main_server.o server.o utilities.o
main_server.o: main_server.c header/server.h header/utilities.h
	cc -c main_server.c
server.o: server.c header/server.h   header/utilities.h
	cc -c server.c
utilities.o: utilities.c header/utilities.h
	cc -c utilities.c
