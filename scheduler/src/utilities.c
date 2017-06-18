#include "utilities.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int stringArrayLen(char *includes[]) {
	size_t count = 0;
	while (includes[count] != NULL)
		count++;
	return count;
}

/* Options : Array of strings with your menu option
 * Header : An header title, not required
 * Footer : A footer sign, not required
 * rowWrap : if true, between options, there is a row
 * evidence : if true, each option has a > prepended
 * */
void printMenu(char *options[], char* header, char* footer, bool rowWrap,
		bool evidence, int lineSize) {
	printRow(lineSize, '~');
	if (header) {
		printf("%s", header);
	}
	printRow(lineSize, '-');
	printf("Select one of these options:");
	for (int i = 0; i < stringArrayLen(options); i++) {
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

void printRow(int a, char lineChar) {
	printf("\n");
	for (int i = 0; i < a; i++) {
		printf("%c", lineChar);
	}
	printf("\n");
}

void clearConsole() {
	system("clear"); /* Or ( "cls" ); for non-POSIX */
}
