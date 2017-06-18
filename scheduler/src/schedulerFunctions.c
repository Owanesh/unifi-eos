#include "schedulerFunctions.h"
#include "utilities.h"

void printMainMenu() {
	char *options[4] = { "(1) Crea un nuovo task",
			"(2) Esegui il task in testa alla coda",
			"(3) Esegui un task specifico", "(4) Elimina un task specifico",
			"(5) Modifica la priorita di un task",
			"(6) Cambiare la politica di scheduling utilizzata",
			"(7) Uscire dal programma", };
	printMenu(options, "Scheduler C", "Busiello and Mauro", false, true, 50);
}
