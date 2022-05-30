#include <printing.h>
#include <scheduler.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6

static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(int exception) //llamado desde interrupts.asm
{
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if (exception == INVALID_OPCODE_ID)
		invalid_opcode();
}

static void zero_division() 
{
	//imprime un error en rojo, printing.c ya sabe que task fue, y por lo tanto en qué screen imprimirlo
	unsigned char* errorMsg = "An error occurred: division by zero exception!";
	format_t fmt = {RED, WHITE};
	print(errorMsg, &fmt); 
	newLine(RED);
	
	//elimina a esta task del scheduler (getCurrentTaskId me da el id de la task activa justo cuando se genero la excepcion)
	int8_t currentTaskId = getCurrentTaskId();
	if(currentTaskId < 0)	//devuelve negativo si el scheduler no tiene ninguna task activa
		return;
	killTask(currentTaskId);
}

static void invalid_opcode()
{
	//imprime un error en rojo, printing.c ya sabe que task fue, y por lo tanto en qué screen imprimirlo
	unsigned char* errorMsg = "An error occurred: invalid opcode exception!";
	format_t fmt = {RED, WHITE};
	print(errorMsg, &fmt);
	newLine(RED);
	
	//elimina a esta task del scheduler (getCurrentTaskId me da el id de la task activa justo cuando se genero la excepcion)
	int8_t currentTaskId = getCurrentTaskId();
	if(currentTaskId < 0)	//devuelve negativo si el scheduler no tiene ninguna task activa
		return;
	killTask(currentTaskId);
}
