#include "header/main_client.h"
#include "header/seeNewMessages.h"

#include <stdio.h>
#include <stdlib.h>

void seeNewMessages() {
	/*
	 * 1) leggo da messages tutte le stringhe salvate e le stampo a video
	 * 2) azzero countMessages
	 */
	int i = 0;
	for (; i < totalMessages; i++) {
		if (i == totalMessages - countMessages)
			printf("- Messaggi non letti -\n");
		printf("Messaggio %d:\n%s\n", i + 1, messages[i]);
	}
	countMessages = 0;
}
