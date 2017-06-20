#ifndef HEADER_UTILITIES_H_
#define HEADER_UTILITIES_H_

#define LENGTH_ARRAY(x)  (sizeof(x) / sizeof((x)[0]))

typedef enum {
	false = 0, true = 1
} bool;

void clearConsole();
void printMenu(const char *options[], char* header, char* footer, bool rowWrap,
		bool evidence, int lineSize);
void printRow(int a, char lineChar);
int stringArrayLen(const char *options[]);
int selectOption(int allowed[2], int disabled[], int dis_length);
int readValue();

#endif /* HEADER_UTILITIES_H_ */
