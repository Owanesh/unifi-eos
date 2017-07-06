#include "header/utilities.h"

#include <stdio.h>
#include <stdlib.h>

/* Controlla la scelta dell'utente ed invoca le funzioni opportune */
void switchOptions(int value) {
	switch (value) {
	case 1:

		break;
	case 2:

		break;
	}
}

int main(int argc, const char **argv) {
	set_argv(argv);
	int optionsAllowed[] = { 1, 3 };
	int value;
	value = selectOption("Selezionare un'opzione del menu': ", optionsAllowed,
	NULL, 0);
	switchOptions(value);
	printf("\nProgramma terminato.");
	exit(EXIT_SUCCESS);
}
