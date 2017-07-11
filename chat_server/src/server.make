server: main_server.o server.o connect.o disconnect.o utilities.o
	cc -o "server" main_server.o server.o connect.o disconnect.o utilities.o
main_server.o: main_server.c header/server.h header/utilities.h
	cc -c main_server.c
server.o: server.c header/server.h  header/utilities.h header/client.h header/disconnect.h
	cc -c server.c
connect.o: connect.c header/connect.h header/utilities.h header/client.h header/server.h
	cc -c connect.c
disconnect.o: disconnect.c header/disconnect.h header/client.h
	cc -c disconnect.c
utilities.o: utilities.c header/utilities.h
	cc -c utilities.c
