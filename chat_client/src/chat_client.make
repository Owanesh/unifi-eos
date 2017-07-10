chat_client: main_client.o connect.o getListOfClients.o sendMessage.o seeNewMessages.o disconnect.o handler_functions.o utilities.o
	cc -o "chat_client" main_client.o connect.o getListOfClients.o sendMessage.o seeNewMessages.o disconnect.o handler_functions.o utilities.o
main_client.o: main_client.c header/main_client.h header/connect.h header/getListOfClients.h header/sendMessage.h header/seeNewMessages.h header/disconnect.h header/handler_functions.h header/utilities.h
	cc -c main_client.c
connect.o: connect.c header/connect.h header/main_client.h
	cc -c connect.c
getListOfClients.o: getListOfClients.c header/main_client.h header/getListOfClients.h
	cc -c getListOfClients.c
sendMessage.o: sendMessage.c header/sendMessage.h header/main_client.h header/utilities.h
	cc -c sendMessage.c
seeNewMessages.o: seeNewMessages.c header/seeNewMessages.h header/main_client.h
	cc -c seeNewMessages.c
disconnect.o: disconnect.c header/disconnect.h header/main_client.h
	cc -c disconnect.c
handler_functions.o: handler_functions.c header/handler_functions.h header/disconnect.h header/main_client.h
	cc -c handler_functions.c
utilities.o: utilities.c header/utilities.h
	cc -c utilities.c
