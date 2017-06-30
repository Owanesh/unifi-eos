#include <stdlib.h>
#include <stdio.h>
#include "header/readCommand.h"

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
	return str;
}
