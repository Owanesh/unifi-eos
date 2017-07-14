chat_server: main_server.o server.o connect.o disconnect.o utilities.o writeClientList.o deliverMessage.o
	cc -o "chat_server" main_server.o server.o connect.o disconnect.o utilities.o writeClientList.o deliverMessage.o
main_server.o: main_server.c header/server.h header/connect.h header/disconnect.h header/writeClientList.h header/deliverMessage.h
	cc -c main_server.c
server.o: server.c header/client.h header/disconnect.h header/connect.h header/utilities.h header/server.h
	cc -c server.c
connect.o: connect.c header/client.h header/connect.h header/utilities.h header/server.h
	cc -c connect.c
disconnect.o: disconnect.c header/client.h header/server.h header/disconnect.h
	cc -c disconnect.c
utilities.o: utilities.c header/utilities.h
	cc -c utilities.c
writeClientList.o: writeClientList.c header/client.h header/writeClientList.h header/server.h
	cc -c writeClientList.c
deliverMessage.o: deliverMessage.c header/deliverMessage.h header/client.h header/server.h
	cc -c deliverMessage.c
