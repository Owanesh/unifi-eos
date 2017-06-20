#define LENGTH_ARRAY(x)  (sizeof(x) / sizeof((x)[0]))

typedef enum {
	false = 0, true = 1
} bool;

void clearConsole();
void printMenu(char *options[], char* header, char* footer, bool rowWrap,
		bool evidence, int lineSize);
void printRow(int a, char lineChar);
int stringArrayLen(char *options[]);
int selectOption(int allowed[2], int disabled[], int dis_length);
int readValue();
