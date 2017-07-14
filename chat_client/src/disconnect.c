#include "header/main_client.h"
#include "header/disconnect.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void disconnect() {
	/*
	 * 1) Invia messaggio di disconnessione al server
	 * 2) chiude la connessione con fdClientPipe e fdServerPipe
	 * 3) libera l'eventuale memoria dei messaggi non letti
	 * 4) torna al menu' principale
	 */
	char msg[50];
	sprintf(msg, "DISCONNECT %d", getpid());
	int length = strlen(msg) + 1; //+1 per '\0'
	write(fdServerPipe, msg, length);
	//il server si occupera' della mia cancellazione dalla lista
	close(fdClientPipe);
	close(fdServerPipe);
	if (messages != NULL) {
		int i = 0;
		for (; i < totalMessages; i++)
			free(messages[i]);
		free(messages);
	}
	messages = NULL;
	countMessages = 0;
	totalMessages = 0;
}
