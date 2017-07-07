#include <stdio.h>
#include <stdlib.h>
#include "header/handler_functions.h"
#include "header/main_client.h"
void handler_termination();
void handler_new_message() {
	countMessages++;
}
void handler_dest_not_found();
