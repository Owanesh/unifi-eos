#include <stdio.h>
#include <stdlib.h>
#include "header/utilities.h"
#include "header/server.h"
#include <sys/stat.h>           /* For S_IFIFO */
#include <fcntl.h>
#include <unistd.h> /* unlink */

int log_enabled=1;

int server_pipe;
char* server_pipe_name = "server_pipe";
void start() {
 	if ( unlink(server_pipe_name) == -1) { //rimuovo la vecchia sessione del server
		perror("\nErrore durante la rimozione della vecchia sessione: ");
	} else if(log_enabled==1) {
		printf("\n[LOG] Rimossa sessione precedente");
	}
	if (mknod(server_pipe_name, S_IFIFO, 0) < 0) {
		perror("\nErrore durante la generazione del pipe: ");
	} else if(log_enabled==1) {
		printf("\n[LOG] Generata nuova sessione");
	}
	if ( chmod(server_pipe_name, 0660) < 0) { //acquisisco i permessi sulla pipe
 		perror("\nErrore durante l'acquisizione dei permessi sul pipe: ");
	} else if(log_enabled==1) {
		printf("\n[LOG] Acquisiti permessi per la sessione corrente (0660)");
	}
	server_pipe = open(server_pipe_name, O_RDONLY); //salvo la pipe per la chiusura
	if (server_pipe == -1) {
		perror("\nPipe creata ma inutilizzabile: ");
	} else if(log_enabled==1) {
		printf("\n[LOG] Il server è pronto!");
	}
}

void stop() {
	close(server_pipe);
	unlink(server_pipe_name);
}

char** getListOfUser(int pidRequest) {
}
void sendMessage(int pidFrom, int pidTo) {
}

