#include "header/utilities.h"
#include "header/sequentialExec.h"
#include "header/parallelExec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// opzioni del menù principale
const char* options[] = { "(1) Esecuzione sequenziale",
		"(2) Esecuzione parallela", "(3) Esci", NULL };

/* Controlla la scelta dell'utente ed invoca le funzioni opportune */
void switchOptions(int value) {
	switch (value) {
	case 1:
		//esecuzione sequenziale
		sequentialExec();
		break;
	case 2:
		//esecuzione parallela
		parallelExec();
		break;
	}
}

int main(int argc, const char **argv) {
	set_argv(argv);
	int optionsAllowed[] = { 1, 3 };
	int value;
	printMenu(options, "Interprete di comandi", NULL, false, true, 50);
	value = selectOption("Selezionare un'opzione del menu': ", optionsAllowed,
	NULL, 0);
	switchOptions(value);
	printf("\nProgramma terminato.");
	exit(EXIT_SUCCESS);
}
