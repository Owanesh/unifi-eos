#include <stdlib.h>
#include <stdio.h>
#include "header/readCommand.h"
#include <string.h>

void str_split(char* input_string, const char token_delimiter, char* *command,
		char** *args);

char* readCommand() {
	char *str;
	int ch, size = 21, len = 0;
	str = realloc(NULL, sizeof(char) * size); //20 caratteri disponibili + '\0'
	if (str == NULL) //errore
		return str;

	while ((ch = fgetc(stdin)) != EOF && ch != '\n') { //lettura fino a EOF o '\n'
		str[len++] = ch;
		if (len == size) {
			str = realloc(str, sizeof(char) * (size += 16)); //rialloco 15 caratteri + '\0'
			if (str == NULL) //errore
				return str;
		}
	}
	str[len++] = '\0'; //terminazione stringa
	str = realloc(str, sizeof(char) * len); //rialloco esattamente lo spazio occupato


	char** args = 0;
	char* command = "";
    str_split(str, ' ', &command, &args);
	/* Test of stringsplit*/
/*
	printf("Il comando e' %s\n", command);
	if (args) {
		int i;
		for (i = 0; *(args + i); i++) {
			printf("parametri=[%s]\n", *(args + i));
			free(*(args + i));
		}
		printf("\n");
		free(args);
	}
*/
	return str;
}





void str_split(char* input_string, const char token_delimiter, char* *command,
		char** *args) {
	//strtok deprecata, ma windows non ha strsep
	char** result_splitted_string_array = 0;
	int token_counter = 0;
	char* temp_string = input_string;
	char delim[2]; //usato per le strok, che vogliono un array
	delim[0] = token_delimiter;
	delim[1] = 0;

	/* Conteggio di quanti token troviamo, scorrendo la stringa caratterre  */
	while (*temp_string) {
		if (token_delimiter == *temp_string) {
			token_counter++;
		}
		temp_string++;
	}

	/* Aggiungo uno spazio di sicurezza per i token finali */
	token_counter++;

	/* Alloco uno spazio di memoria atto a contenere il numero di token trovati */
	result_splitted_string_array = malloc(sizeof(char*) * ++token_counter);

	if (result_splitted_string_array != NULL) {
		int id_tok = 0;
		char* token = strtok(input_string, delim); //divide la stringa in sottostringhe, usa toke_delimiter per capire

		/* preso il token successivo (strtok), controllo se e' valido*/
		while (token != NULL) {
			if (id_tok == 0) { //se è il primo in assoluto, allora e' il comando e non un argomento
				*command = strdup(token); //clona dinamicamente la stringa token e la mette in command
				token = strtok(0, delim);
			}
			*(result_splitted_string_array + id_tok) = strdup(token);
			//nello spazio zero, ci sara' il secondo blocco, perche strtok sara' gia stato eseguito
			token = strtok(0, delim);
			id_tok++;
		}
		*(result_splitted_string_array + id_tok) = 0;
	}
	*args = result_splitted_string_array;

}

