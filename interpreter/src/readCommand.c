#include <stdlib.h>
#include <stdio.h>
#include "header/readCommand.h"
#include "header/utilities.h"
#include <string.h>

int countFields(char* str, const char token_delimiter);
void str_split(char* input_string, const char token_delimiter, char** args);

/*
 * Restituisce il comando digitato dall'utente trimmato (senza spazi ne' all'inizio ne' alla fine)
 */
char* readCommand() {
	char *str;
	int ch, size = 21, len = 0;
	str = realloc(NULL, sizeof(char) * size); //20 caratteri disponibili + '\0'
	if (str == NULL) //errore
		return NULL;

	while ((ch = fgetc(stdin)) != EOF && ch != '\n') { //lettura fino a EOF o '\n'
		str[len++] = ch;
		if (len == size) {
			str = realloc(str, sizeof(char) * (size += 16)); //rialloco 15 caratteri + '\0'
			if (str == NULL) //errore
				return NULL;
		}
	}
	str[len++] = '\0'; //Terminazione stringa
	str = realloc(str, sizeof(char) * len); //Rialloco esattamente lo spazio occupato
	str = trim(str); // elimino spazi iniziali e finali
	return str;
}

char** parseCommand(char *command) {
	int num_of_args = countFields(command, ' ');
	char** args = malloc(sizeof(char*) * num_of_args);
	str_split(command, ' ', args);
	free(command); //free del comando istanziato in readCommand
	return args;
}

int countFields(char* str, const char token_delimiter) {
	int token_counter = 0;

	/* Conteggio di quanti token troviamo, scorrendo la stringa caratterre  */
	while (*str) {
		if (token_delimiter == *str) {
			token_counter++;
		}
		str++;
	}
	//+2 per il comando e per il NULL finale
	token_counter += 2;
	return token_counter;
}

void str_split(char* input_string, const char token_delimiter, char** args) {
	int id_tok = 0;
	char delim[] = { token_delimiter, '\0' };
	char* token = strtok(input_string, delim);
	/* Preso il token successivo (strtok), controllo se e' valido*/
	while (token != NULL) {
		args[id_tok] = strdup(token);
		token = strtok(0, delim);
		id_tok++;
	}
	args[id_tok] = NULL;
}

