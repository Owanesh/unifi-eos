#define UTILITIES_H_
/* Boolean type definition */
typedef enum {
	false = 0, true = 1
} bool;

void clearConsole();
void printMenu(char *options[], char* header, char* footer, bool rowWrap,
		bool evidence, int lineSize);
void printRow(int a, char lineChar);
int stringArrayLen(char *includes[]);
