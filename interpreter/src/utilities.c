#include "header/utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

/*
 * Acquisisce una linea di testo da stdin verificando che non sia:
 * TOO_LONG = la stringa è troppo lunga
 * INVALID = la stringa inizia con ' ' or '\n'
 * NO_INPUT = errore di I/O
 */
int getLine(char *buff, size_t sz) {
	int ch, extra;

	if (fgets(buff, sz, stdin) == NULL)
		return NO_INPUT;
	if (buff[0] == ' ' || buff[0] == '\n')
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

/* Restituisce un valore intero indicante la dimensione di un
 * array di stringhe, avente come ultimo valore, un valore di tipo NULL
 * Usato per contare le opzioni del menù
 */
int stringArrayLen(const char *options[]) {
	int count = 0;
	while (options[count] != NULL)
		count++;
	return count;
}

/* Options : opzioni del menù
 * Header : header title, non obbligatorio
 * Footer : footer title, non obbligatorio
 * rowWrap : se true viene inserita una riga tra le opzioni
 * evidence : se true viene inserito '>' all'inizio di ogni opzione
 * */
void printMenu(const char *options[], char* header, char* footer, bool rowWrap,
		bool evidence, int lineSize) {
	printRow(lineSize, '~');
	if (header) {
		printf("%s", header);
	}
	printRow(lineSize, '-');
	int i = 0;
	for (; i < stringArrayLen(options); i++) {
		if (i > 0)
			printf("\n");
		if (evidence) {
			printf("\t> ");
		}
		printf(" %s ", options[i]);
		if (rowWrap) {
			printRow(lineSize, '-');
		}
	}

	printRow(lineSize, '-');
	if (footer) {
		printf("%s", footer);
		printRow(lineSize, '~');
	}
}

/* Riceve in input un valore intero (A) ed un carattere,
 * stampa per A volte il carattere, contenuto tra due righe vuote
 */
void printRow(int a, char lineChar) {
	printf("\n");
	int i = 0;
	for (; i < a; i++) {
		printf("%c", lineChar);
	}
	printf("\n");
}

/*
 * Controlla che 'num' sia compreso nel range e che sia diverso da un valore disabilitato.
 * Se alloweRange == NULL allora ogni valore è valido (a meno di valori disabilitati).
 * Restituisce true se il valore digitato è valido, altrimenti false.
 */
bool isValueAllowed(int num, int allowedRange[2], int disabled[],
		int disabled_length) {
	bool valid = true;
	bool inRange =
			(allowedRange == NULL)
					|| (num >= allowedRange[0] && num <= allowedRange[1]) ?
					true : false;
	int i = 0;
	for (; (i < disabled_length) && valid && inRange; i++) {
		if (num == disabled[i])
			valid = false;
	}
	return valid && inRange;
}

/*
 * Consente di selezionare un'opzione specificata nel range di optionsAllowed.
 * allowed[2]-> allowed[0]=min value / allowed[1]=max value
 * disabled[]-> opzioni non valide
 * dis_length-> cardinalità dell'insieme dei valori disabilitati
 * Restituisce il valore valido digitato dall'utente.
 */
int selectOption(char *prompt, int allowed[2], int disabled[], int dis_length) {
	int value;
	bool valid = false;
	while (!valid) {
		if (prompt != NULL) {
			printf("%s", prompt);
		}
		value = readValue();
		if (!isValueAllowed(value, allowed, disabled, dis_length)) {
			printf("Il valore inserito non risulta nelle opzioni. Riprovare\n");
		} else {
			valid = true;
		}
	}
	return value;
}

/* readValue(): restituisce il valore inserito da stind
 Consente:
 - spazi iniziali : " 123"
 - spazi finali : "123 "
 - zeri iniziali : "00000123"
 Controlla i seguenti errori:
 - No input : ""
 - testo prima di un numero : "abc 123"
 - caratteri speciali : "--123"
 */
int readValue() {
	int value;
	int validSyntax;
	char buffer[100];
	do {
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			//errore di lettura, uscita forzata
			return false;
		}
		// una carattere iniziale resituirebbe 0
		validSyntax = sscanf(buffer, "%d", &value) && buffer[0] != '\n'
				&& buffer[0] != ' ';
		if (validSyntax != 1)
			printf("Input sintatticamente non valido. Riprovare: ");
	} while (!validSyntax);
	return value;
}

