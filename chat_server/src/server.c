#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>           /* For S_IFIFO */
#include <fcntl.h>
#include <unistd.h> /* unlink */
#include <string.h>
#include "header/client.h"
#include "header/disconnect.h"
#include "header/connect.h"
#include "header/utilities.h"
#include "header/server.h"

char* server_pipe_name = "../server_pipe";

void openServerPipe();

void start() {
	createPipe(server_pipe_name);
	openServerPipe();

	// l'apertura non deve essere bloccante, ma le successive read sì, perciò modifico i flag
	int saved_flags = fcntl(server_pipe, F_GETFL);
	// maschero O_NONBLOCK
	fcntl(server_pipe, F_SETFL, saved_flags & (~O_NONBLOCK));
}

void openServerPipe() {
	/* apertura della server_pipe in lettura e ovviamente
	 * non bloccante, dato che non è necessario che esistano client gia' in attesa*/
	server_pipe = open(server_pipe_name, O_RDONLY | O_NONBLOCK);
	if (server_pipe == -1) {
		printf("\n[ERROR] (%s) Pipe creata ma inutilizzabile",
				server_pipe_name);
	} else if (verboseMode == 1) {
		printf("\n[LOG] (%s) La pipe è pronta!", server_pipe_name);
		fflush(stdout);
	}
}

void stop() {
	closeConnection(server_pipe, server_pipe_name);
}

/* Ritorna il nome completo della pipe di un client
 * pid + "_client_pipe" */
void getClientPipePath(pid_t pid, char* bufferPath) {
	sprintf(bufferPath, "../%d%s", pid, "_client_pipe");
}

/* Ritorna un puntatore all'ultimo client della lista */
Client* getLastClient(Client *head) {
	if (head == NULL) {
		return NULL;
	}
	Client *last = head;
	while (last->next != NULL) {
		last = last->next;
	}
	return last;
}

/*
 * Legge il comando ricevuto in server_pipe, inserendolo in "str"
 * Restituisce 1 se è presente un comando nella stringa, altrimenti 0
 */
int readCommand(char **str) {
	int dim = 512;
	/* non essendo possibile prevedere la lunghezza massima del messaggio ricevuto
	 * si alloca dinamicamente lo spazio del buffer
	 */
	*str = realloc(*str, sizeof(char) * dim);
	char* temp = *str;
	int n, count = 0;
	do { // Legge fino a '\0' o EOF
		/*
		 * Nota: la read è bloccante fino a che c'è almeno un client connesso,
		 * altrimenti legge EOF ed esce, rientrando ed uscendo all'infinito.
		 */
		n = read(server_pipe, temp, 1);
		if (n != 0) {
			count++;
			if (count == dim) {
				//rialloco il doppio della dimensione precedente
				temp = realloc(temp, sizeof(char) * (dim * 2));
				dim *= 2;
				temp += (count - 1); //riposiziono il puntatore
			}
		} else {
			**str = '\0';
		}
	} while (n > 0 && *temp++ != '\0');
	return n;
}

/*
 * Acquisisce il primo campo della stringa ricevuta,
 * ovvero la keyword che identifica il tipo di comando e
 * la inserisce nella variabile keyword
 */
void getFirstField(char keyword[20], char* cmd) {
	int i = 0;
	while (*cmd != ' ' && *cmd != '\0') {
		keyword[i] = *cmd;
		cmd++;
		i++;
	}
	keyword[i] = '\0';
}

/*
 * Ottiene il pid dai comandi con la seguente sintassi
 * "<COMMAND> <pid>"
 */
void getPidFromCmd(char* cmd, pid_t* pid) {
	int i = 0;
	char temp[20];
// raggiungo il primo spazio
	while (*cmd != ' ') {
		cmd++;
	}
	cmd++;
// copio il pid
	while (*cmd != '\0') {
		temp[i] = *cmd;
		cmd++;
		i++;
	}
	temp[i] = '\0';
	*pid = strtol(temp, NULL, 10);
}

/*
 * Ottiene il file descriptor della pipe del client individuato da pid.
 * Restituisce 0 se il client non esiste, altrimenti restituisce il fd.
 */
int getPipeByPid(pid_t pid, Client* head) {
	if (head == NULL) {
		return 0;
	} else {
		int found = 0;
		do {
			if (head->pid == pid)
				// il valore della pipe sarà sicuramente diverso da 0
				found = head->pipe;
			head = head->next;
		} while (found == 0 && head != NULL);
		return found;
	}
}
