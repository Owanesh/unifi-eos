#ifndef HEADER_UTILITIES_H_
#define HEADER_UTILITIES_H_

#include <stdio.h>
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define INVALID 3
#define LENGTH_ARRAY(x)  (sizeof(x) / sizeof((x)[0]))

/* Definizione del tipo di una variabile booleana */
typedef enum {
	false = 0, true = 1
} bool;

/*
 * Acquisisce una linea di testo da stdin verificando che non sia:
 * TOO_LONG = la stringa è troppo lunga
 * INVALID = la stringa inizia con ' ' or '\n'
 * NO_INPUT = errore di I/O
 */
int getLine(char *buff, size_t sz);
/* Options : opzioni del menù
 * Header : header title, non obbligatorio
 * Footer : footer title, non obbligatorio
 * rowWrap : se true viene inserita una riga tra le opzioni
 * evidence : se true viene inserito '>' all'inizio di ogni opzione
 * */
void printMenu(const char *options[], char* header, char* footer, bool rowWrap,
		bool evidence, int lineSize);
void printRow(int a, char lineChar);
/*
 * Conta le opzioni del menù
 */
int stringArrayLen(const char *options[]);
/*
 * Consente di selezionare un'opzione specificata nel range di optionsAllowed.
 * allowed[2]-> allowed[0]=min value / allowed[1]=max value
 * disabled[]-> opzioni non valide
 * dis_length-> cardinalità dell'insieme dei valori disabilitati
 * Restituisce il valore valido digitato dall'utente.
 */
int selectOption(char *prompt, int allowed[2], int disabled[], int dis_length);
/* readValue(): restituisce il valore inserito da stind
 Consente:
 - spazi iniziali : " 123"
 - spazi finali : "123 "
 - zeri iniziali : "00000123"
 Controlla i seguenti errori:
 - No input : ""
 - testo prima di un numero : "abc 123"
 - caratteri speciali : "--123"
 */
int readValue();

char *trim(char *str);

char** argv;
void set_argv(const char **args);

#endif /* HEADER_UTILITIES_H_ */
