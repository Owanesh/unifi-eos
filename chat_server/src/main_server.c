#include "header/server.h"
#include "header/connect.h"
#include "header/disconnect.h"
#include "header/writeClientList.h"
#include "header/deliverMessage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

// puntatore alla testa della lista dei client
Client *head = NULL;
//definizione delle variabile extern dichiarate in main_client.h
int server_pipe = 0;
// buffer per ogni comando letto da server_pipe
char* command = NULL;
char* server_pipe_path = "./server_pipe";

void switchCommand(char* cmd);
void handler_termination();

int main(void) {
	if (access(server_pipe_path, F_OK) != -1) {
		// se il file server_pipe esiste, allora un processo server è già operativo
		printf(
				"[ERROR] Esiste già un processo server operativo. Impossibile avviarne più di uno contemporaneamente.");
	} else {
		// il processo puo' essere correttamente avviato
 		start();
		signal(SIGINT, handler_termination);
		printf("\n\n");
		while (1) {
			int isCmd = readCommand(&command);
			if (isCmd){
				printf("\n%s\n", command);
				switchCommand(command);
			}
		}
	}
}

void switchCommand(char* cmd) {
	char keyword[20];
	getFirstField(keyword, cmd);
	if (strcmp(keyword, "LIST") == 0) {
		// "LIST <pid>"
		printf("\nLIST cmd request ");
		writeClientList(head, cmd);

	} else if (strcmp(keyword, "CONNECT") == 0) {
		// "CONNECT <pid>"
		printf("\nCONNECT cmd request ");
		acceptConnection(&head, cmd);

	} else if (strcmp(keyword, "MSG") == 0) {
		// "MSG <pid_destinatari> $<pid_mittente> <messaggio>"
		printf("\nMSG cmd request ");
		deliverMessage(head, cmd);

	} else if (strcmp(keyword, "DISCONNECT") == 0) {
		// "DISCONNECT <pid>"
		printf("\nDISCONNECT cmd request ");
		disconnect(&head, cmd);

	} else {
		printf("\"<%s>\": Comando non riconosciuto", cmd);
	}
}

void handler_termination() {
	/*
	 * 1) Libera la memoria di ogni nodo della lista e chiude/elimina le pipe
	 * 2) Chiude ed elimina la connessione con server_pipe
	 * 3) libera command
	 */
	Client* ptr;
	while (head != NULL) {
		ptr = head;
		close(ptr->pipe);
		char* temp = malloc(sizeof(char) * 50);
		getClientPipePath(ptr->pid, temp);
		unlink(temp);
		free(temp);
		head = head->next;
		free(ptr);
	}
	close(server_pipe);
	unlink(server_pipe_path);
	free(command);
	printf("\nIl server e' terminato con successo.");
	exit(EXIT_SUCCESS);
}
