#ifndef HEADER_UTILITIES_H_
#define HEADER_UTILITIES_H_

#include <stdio.h>
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define INVALID 3
#define LENGTH_ARRAY(x)  (sizeof(x) / sizeof((x)[0]))

typedef enum {
	false = 0, true = 1
} bool;

/*
 * ALlows to get a line from stdin checking that is not
 * TOO_LONG = the string has more characters than sz
 * INVALID = the string starts with ' ' or '\n'
 * NO_INPUT = read error
 */
int getLine(char *buff, size_t sz);
/* Options : Array of strings with your menu option
 * Header : An header title, not required
 * Footer : A footer sign, not required
 * rowWrap : if true, between options, there is a row
 * evidence : if true, each option has a > prepended
 * */
void printMenu(const char *options[], char* header, char* footer, bool rowWrap,
		bool evidence, int lineSize);
void printRow(int a, char lineChar);
/*
 * Counts the rows of options matrix
 */
int stringArrayLen(const char *options[]);
/*
 * Allows to select an option between the range allowed
 * allowed[2]-> allowed[0]=min value / allowed[1]=max value
 * disabled[]-> selections forbidden
 * dis_length-> length of disabled[]
 * Returns the value inserted
 */
int selectOption(char *prompt, int allowed[2], int disabled[], int dis_length);
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
int readValue();

#endif /* HEADER_UTILITIES_H_ */
