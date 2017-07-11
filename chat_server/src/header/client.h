#ifndef HEADER_CLIENT_H_
#define HEADER_CLIENT_H_


typedef struct Client {
	pid_t pid;
	struct Client *next;
} Client ;



#endif /* HEADER_CLIENT_H_ */
