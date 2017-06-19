#include "header/schedulerFunctions.h"
#include "header/utilities.h"
#include <stdio.h>

void printMainMenu() {
	char *options[] = { "(1) Crea un nuovo task",
			"(2) Esegui il task in testa alla coda",
			"(3) Esegui un task specifico", "(4) Elimina un task specifico",
			"(5) Modifica la priorita di un task",
			"(6) Cambiare la politica di scheduling utilizzata",
			"(7) Uscire dal programma",NULL};
	printMenu(options, "Scheduler C", "Busiello and Mauro", false, true, 50);
}
