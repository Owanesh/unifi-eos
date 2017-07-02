#include <stdlib.h>
#include <stdio.h>
#include "header/readCommand.h"
#include "header/utilities.h"
#include <string.h>

void str_split(char* input_string, const char token_delimiter, char* *command,
		char** *args);

char** readCommand() {
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
	char* trimmedStr = trim(str);
	free(str); // non serve piu'
	if (trimmedStr == NULL) {
		// L'utente non ha inserito nessun comando
		return NULL;
	} else {
		char** args = 0;
		char* command = "";
		str_split(trimmedStr, ' ', &command, &args);
		/* Test of stringsplit*/
		printf("\nIl comando e' %s\n", command);
		if (args) {
			int i;
			for (i = 0; *(args + i); i++) {
				printf("parametri=[%s]\n", *(args + i));
				free(*(args + i));
			}
			printf("\n");
			free(args);
		}
		return args;
	}
}

void str_split(char* input_string, const char token_delimiter, char* *command,
		char** *args) {
	//strtok deprecata, ma windows non ha strsep
	char** result_splitted_string_array = NULL;
	int token_counter = 0;
	char* temp_string = input_string;
	char delim[2]; //Usato per le strok, che vogliono un array
	delim[0] = token_delimiter;
	delim[1] = 0;

	/* Conteggio di quanti token troviamo, scorrendo la stringa caratterre  */
	while (*temp_string) {
		if (token_delimiter == *temp_string) {
			token_counter++;
		}
		temp_string++;
	}
	if (token_counter > 0) {	 //Ho trovato almeno un token
		/* Alloco uno spazio di memoria atto a contenere il numero di token trovati */
		result_splitted_string_array = malloc(sizeof(char*) * ++token_counter);
	}
	if (result_splitted_string_array != NULL) {
		int id_tok = 0;
		char* token = strtok(input_string, delim);
		/* Preso il token successivo (strtok), controllo se e' valido*/
		while (token != NULL) {
			if (id_tok == 0) { //se è il primo in assoluto, allora e' il comando e non un argomento
				*command = strdup(token); //clona dinamicamente la stringa token e la mette in command
				token = strtok(0, delim);
			}
			*(result_splitted_string_array + id_tok) = strdup(token);
			//Nello spazio zero, ci sara' il secondo blocco, perche strtok sara' gia stato eseguito
			token = strtok(0, delim);
			id_tok++;
		}
		*(result_splitted_string_array + id_tok) = 0;
	} else {
		//Non ho trovato token, quindi la stringa arrivata equivale al comando
		*command = input_string;
	}
	*args = result_splitted_string_array;
}

