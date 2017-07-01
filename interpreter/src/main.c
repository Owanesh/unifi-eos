#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "header/sequentialExec.h"
#include "header/parallelExec.h"
#include "header/utilities.h"

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
	default:
		printf("\nProgramma terminato.");
	}
}

int main(void) {
	int optionsAllowed[] = { 1, 3 };
	int value;
	printMenu(options, "Interprete di comandi", NULL, false, true, 50);
	value = selectOption("Selezionare un'opzione del menu': ", optionsAllowed,
	NULL, 0);
	switchOptions(value);
}
