#include "header/main_client.h"
#include "header/seeNewMessages.h"

#include <stdio.h>
#include <stdlib.h>

void seeNewMessages() {
	/*
	 * 1) Se supera il controllo, leggo da messages tutte le stringhe salvate (tante quante indicate da countMessages) e le stampo a video
	 * 2) Libero lo spazio occupato da messages
	 * 3) azzero countMessages
	 */
	if (countMessages == 0) {
		printf("Non ci sono nuovi messaggi.\n");
		return;
	}
	int i = 0;
	for (; i < countMessages; i++) {
		printf("Messaggio %d:\n%s\n", i + 1, messages[i]);
	}
	for (i = 0; i < countMessages; i++) {
		free(messages[i]);
	}
	free(messages);
	countMessages = 0;
}
