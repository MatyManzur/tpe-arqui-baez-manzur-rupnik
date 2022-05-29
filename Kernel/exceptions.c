#include <printing.h>
#include <scheduler.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6

static void zero_division();
static void invalid_opcode();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if(exception == INVALID_OPCODE_ID)
		invalid_opcode();
}

static void zero_division() 
{
	unsigned char* errorMsg = "An error occurred: division by zero exception!";
	format_t fmt = {RED, WHITE};
	print(errorMsg, &fmt);
	newLine(RED);
	int8_t currentTaskId = getCurrentTaskId();
	if(currentTaskId < 0)
		return;
	killTask(currentTaskId);
}

static void invalid_opcode()
{
	unsigned char* errorMsg = "An error occurred: invalid opcode exception!";
	format_t fmt = {RED, WHITE};
	print(errorMsg, &fmt);
	newLine(RED);
	int8_t currentTaskId = getCurrentTaskId();
	if(currentTaskId < 0)
		return;
	killTask(currentTaskId);
}
