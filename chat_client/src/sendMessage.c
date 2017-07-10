#include "header/main_client.h"
#include "header/sendMessage.h"
#include "header/utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int getMessage(char* message);
int readLine();
int getReceivers(char** receivers);
int getValue();
void buildMessage(char* message, char** receivers, int count);

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
	if (message == NULL)
		exit(EXIT_FAILURE);
	char** receivers = NULL;
	int result = getMessage(message);
	if (result == OK) {
		result = getReceivers(receivers);
	}
	if (result != 0) {
		//result contiene il numero di destinatari
		buildMessage(message, receivers, result);
		//il messaggio è pronto per essere inviato al server
		write(fdServerPipe, message, strlen(message) + 1); //+1 perche' strlen non conta '\0'
	} else if (result == 0) {
		printf("Messaggio non inviato.\n");
	}
	// free di tutta la memoria allocata
	if (message != NULL)
		free(message);
	if (receivers != NULL) {
		int i = 0;
		for (; i < result; i++) {
			free(*(receivers + i));
		}
		free(receivers);
	}
}

int getMessage(char* message) {
	int result;
	printf("Inserisci messaggio (MAX %d caratteri).\n", MAX_LENGTH_MSG);
	result = readLine(message, sizeof(char[MAX_LENGTH_MSG]));
	if (result == TOO_LONG) {
		printf("Messaggio troppo lungo. Messaggio non inviato.\n");
	} else if (result == NO_INPUT) {
		printf("Errore di lettura.\n");
	} else if (result == INVALID) {
		printf("Nessun carattere inserito. Messaggio non inviato.\n");
	}
	return result;
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
 * return > 0 -> il client ha inserito i destinatari desiderati
 * return 0 -> il client non vuole più inviare il messaggio e annulla l'operazione
 */
int getReceivers(char** receivers) {
	int count = 0, pid;
	do {
		printf(
				"Inserisci PID del processo destinatario (0 per annullare, INVIO per terminare): ");
		pid = getValue();
		if (pid != -1 && pid != 0) {
			count++;
			//riallocazione di count puntatori
			receivers = realloc(receivers, sizeof(char*) * count);
			if (receivers == NULL)
				exit(EXIT_FAILURE);
			//allocazione e inserimento dell'ultimo pid inserito
			int digits = countDigits(pid) + 1; //+1 per il '\0'
			*(receivers + count - 1) = malloc(sizeof(char) * digits);
			if (*(receivers + count - 1) == NULL)
				exit(EXIT_FAILURE);
			sprintf(*(receivers + count - 1), "%d", pid);
		} else if (pid == -1) {
			count = 0; //azzerando count il messaggio non verrà inviato
		}
	} while (pid != -1 && pid != 0);
	return count;
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
/*
 * Inserisce in "message" la stringa opportunamente formattata
 * MSG <pid_dest1> ... <pid_destN> <pid_mittente> <message>
 */
void buildMessage(char* message, char** receivers, int count) {
	/*
	 * 1) calcolo la dimensione del messaggio finale
	 * 2) copio "MSG " in un variabile d'appoggio "temp"
	 * 3) concateno tutti i destinatari separati da uno spazio
	 * 4) concateno il pid mittente
	 * 5) concateno il messaggio
	 * 6) rialloco lo spazio in message
	 * 7) copio il contenuto di temp in message
	 */
	// "MSG " -> 4 caratteri
	int dimension_message = 4, i;
	for (i = 0; i < count; i++) {
		dimension_message += strlen(*(receivers + i)) + 1;	//+1 per lo spazio
	}
	dimension_message += (countDigits(getpid()) + 1); //+1 spazio
	dimension_message += strlen(message) + 1; //+1 per '\0'
	char* temp = malloc(sizeof(char) * dimension_message);
	if (temp == NULL)
		exit(EXIT_FAILURE);
	//concateno i dati
	strcpy(temp, "MSG ");
	for (i = 0; i < count; i++) {
		strcat(temp, *(receivers + i));
		strcat(temp, " ");
	}
	char* mypid = malloc(sizeof(char) * (countDigits(getpid()) + 3)); //+3 per '$' iniziale, ' ' e '\0' finali
	if (mypid == NULL)
		exit(EXIT_FAILURE);
	sprintf(mypid, "$%d ", getpid());
	strcat(temp, mypid);
	strcat(temp, message);
	message = realloc(message, sizeof(char) * (strlen(temp) + 1));
	strcpy(message, temp);
	free(temp);
	free(mypid);
}
