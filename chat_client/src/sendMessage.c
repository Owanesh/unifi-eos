#include "header/sendMessage.h"
#include "header/main_client.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LENGTH_MSG 4096
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define INVALID 3

int getMessage(char* message);
int readLine();

void sendMessage() {
	/*
	 * Connessione a server_pipe e client_pipe gia' effettuata e reperibile in main_client.h
	 * 1) acquisire il messaggio da parte dell'utente
	 * 2) verificare che sia non troppo lungo e che ci siano caratteri
	 * 3) se il messaggio è valido, impacchetare la stringa con "MSG "
	 */
	//
	char* message = malloc(sizeof(char) * MAX_LENGTH_MSG);
	int result = getMessage(message);

}

int getMessage(char* message) {
	int rc;
	printf("Inserisci messaggio (MAX %d caratteri).\n", MAX_LENGTH_MSG);
	rc = readLine(message, sizeof(char[MAX_LENGTH_MSG]));
	if (rc == TOO_LONG) {
		printf("Messaggio troppo lungo. Messaggio non inviato.\n");
	} else if (rc == NO_INPUT) {
		printf("Errore di lettura.\n");
	} else if (rc == INVALID) {
		printf("Nessun carattere inserito. Messaggio non inviato.\n");
	}
	return rc;
}

/*
 * Acquisisce una linea di testo da stdin verificando che non sia:
 * TOO_LONG = la stringa è troppo lunga
 * INVALID = la stringa non contiene caratteri
 * NO_INPUT = errore di I/O
 */
int readLine(char *buff, size_t sz) {
	int ch, extra;
	if (fgets(buff, sz, stdin) == NULL)
		return NO_INPUT;
	char* temp = buff;
	//controllo che ci sia almeno un carattere e non solo spazi
	while (*temp == ' ') {
		temp++;
	}
	if (*temp == '\n')
		return INVALID;
	// se la stringa fosse troppo lunga non ci sarebbe carattere di newline
	// è necessario rimuovere le digitazioni presente nel buffer input
	// per non influenzare le prossime richieste
	if (buff[strlen(buff) - 1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? TOO_LONG : OK;
	}

	// rimozione del carattere newline
	buff[strlen(buff) - 1] = '\0';
	return OK;
}
