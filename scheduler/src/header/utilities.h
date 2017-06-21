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

int getLine(char *buff, size_t sz);
void printMenu(const char *options[], char* header, char* footer, bool rowWrap,
		bool evidence, int lineSize);
void printRow(int a, char lineChar);
int stringArrayLen(const char *options[]);
int selectOption(int allowed[2], int disabled[], int dis_length);
int readValue();

#endif /* HEADER_UTILITIES_H_ */
