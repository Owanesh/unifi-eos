#include "header/utilities.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
 * Counts the rows of options matrix
 */
int stringArrayLen(char *options[]) {
	int count = 0;
	while (options[count] != NULL)
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
	for (int i = 0; i < stringArrayLen(options); i++) {
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

/*
 * Verifies num checking if it stands between the range and if it's not disabled.
 * If you want to not specify a range set allowedRange to NULL.
 * Return true if it's available, otherwise false
 */
bool isValueAllowed(int num, int allowedRange[2], int disabled[],
		int disabled_length) {
	bool valid = true;
	//inRange == true if numis between range or if allowedRange[0]>=allowedRange[1]
	bool inRange =
			(allowedRange == NULL)
					|| (num >= allowedRange[0] && num <= allowedRange[1]) ?
					true : false;
	for (int i = 0; (i < disabled_length) && valid && inRange; i++) {
		if (num == disabled[i])
			valid = false;
	}
	return valid && inRange;
}

/*
 * Allows to select an option between the range allowed
 * allowed[2]-> allowed[0]=min value / allowed[1]=max value
 * disabled[]-> selections forbidden
 * dis_length-> length of disabled[]
 * Returns the value inserted
 */
int selectOption(int allowed[2], int disabled[], int dis_length) {
	int value;
	bool valid = false;
	while (!valid) {
		value = readValue();
		if (!isValueAllowed(value, allowed, disabled, dis_length)) {
			printf("Il valore inserito non risulta nelle opzioni. Riprovare\n");
		} else {
			valid = true;
		}
	}
	return value;
}

/* readValue(): return the value read
 Allows
 - leading spaces : " 123"
 - trailing spaces : "123 "
 - leading zeros : "00000123"
 - Rescans after error input.
 Catches the following errors
 - No input : ""
 - Text before the number : "abc 123"
 - other : "--123"
 */
int readValue() {
	int value;
	int validSyntax;
	char buffer[100];
	do {
		fputs("\nInserisci la tua scelta > ", stdout);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			//errore di lettura, uscita forzata
			return false;
		}
		// una carattere iniziale resituirebbe 0
		validSyntax = sscanf(buffer, "%d", &value) && buffer[0] != '\n'
				&& buffer[0] != ' ';

		if (validSyntax != 1)
			fputs("Input sintatticamente non valido. Riprovare.\n", stdout);
	} while (!validSyntax);
	return value;
}

