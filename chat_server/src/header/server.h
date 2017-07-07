#ifndef HEADER_SERVER_H_
#define HEADER_SERVER_H_

struct Client {
	pid_t pid;
	struct Client *next;
};

void start();

void stop();

char** getListOfUser(int pidRequest);
void sendMessage(int pidFrom, int pidTo);



#endif /* HEADER_SERVER_H_ */
