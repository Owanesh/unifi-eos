#include "header/sendMessage.h"
#include "header/main_client.h"
#include "header/utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LENGTH_MSG 4096

int getMessage(char* message);
int readLine();
int getReceivers(char** receivers);
int getValue();

void sendMessage() {
	/*
	 * Connessione a server_pipe e client_pipe gia' effettuata e reperibile in main_client.h
	 * 1) acquisire il messaggio da parte dell'utente
	 * 2) verificare che sia non troppo lungo e che ci siano caratteri
	 * 3) se il messaggio è valido, richiedere uno o più destinatari
	 * 4) impacchettare il messaggio come da protocollo
	 *    -> "MSG <pid_destinatari> <pid_mittente> <messaggio>"
	 */
	//
	char* message = malloc(sizeof(char) * MAX_LENGTH_MSG);
	char** receivers = NULL;
	int result = getMessage(message);
	if (result == OK) {
		result = getReceivers(receivers);
	}
	if (result != 0) {
		//result contiene il numero di destinatari
	}
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
	/*se la stringa fosse troppo lunga non ci sarebbe carattere di newline
	 è necessario rimuovere le digitazioni presente nel buffer input
	 per non influenzare le prossime richieste*/
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

/*
 * Acquisisce dall'utente un determinato numero di pid,
 * termina quando l'utente digita \n oppure annulla l'invio del messaggio digitando 0+invio
 */
int getReceivers(char** receivers) {
	int count = 0, pid;
	do {
		printf("Inserisci PID del processo destinatario: ");
		pid = getValue();
	} while (pid != -1 && pid != 0);
}

/*
 * return 0 -> il client ha inserito i destinatari desiderati
 * return -1 -> il client non vuole più inviare il messaggio e annulla l'operazione
 */
int getValue() {
	int value;
	int validSyntax = 0;
	char buffer[100];
	do {
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			//errore di lettura, uscita forzata
			return -1;
		}

		char* bufferTrimmed = trim(buffer);
		//trim restituisce NULL se l'utente ha digitato solo "{' '}\n"
		if (bufferTrimmed != NULL) {
			if (bufferTrimmed[0] == '\n') {
				return 0; //fine inserimento
			}
			// un carattere iniziale resituirebbe 0
			validSyntax = sscanf(bufferTrimmed, "%d", &value)
					&& bufferTrimmed[0] != ' ';
		}
		if (validSyntax != 1)
			printf("Input sintatticamente non valido. Riprovare: ");
	} while (!validSyntax);
	// se value==0 allora l'utente vuole annullare l'operazione e restituisco -1
	// altrimenti restituisco value che e' il pid del destinatario
	return value == 0 ? -1 : value;
}
