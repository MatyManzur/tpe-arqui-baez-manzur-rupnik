#include <scheduler.h>

uint8_t getCurrentTaskId()
{
	return 0; //para que ande el printeo
}

void initializePrinting() //borrar cuando se haga el scheduler posta
{
	addTaskState(0, 0, 0, 24, 79);
}
