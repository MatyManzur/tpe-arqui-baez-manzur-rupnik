#include <printing.h>

static uint8_t * const video = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;

typedef struct point_t
{
	uint8_t row;
	uint8_t column;
} point_t;

typedef struct taskState_t
{
	point_t topLeft;
	point_t bottomRight;
	point_t cursor;
} taskState_t;

static taskState_t taskStates[MAX_TASK_COUNT];

static uint8_t* pointToCursor(point_t point)
{
	return (uint8_t*)(video + 2*(point.row * width + point.column));
}

void addTaskState(uint8_t taskId, uint8_t topLeftRow, uint8_t topLeftColumn, uint8_t bottomRightRow, uint8_t bottomRightColumn)
{
	if(taskId >= MAX_TASK_COUNT)
		return;
	
	if(topLeftRow >= height)
		topLeftRow = height - 1;
	if(topLeftColumn >= width)
		topLeftColumn = width - 1;
	
	if(bottomRightRow >= height)
		bottomRightRow = height - 1;
	if(bottomRightColumn >= width)
		bottomRightColumn = width - 1;
	
	point_t topLeft = { .row = topLeftRow, .column = topLeftColumn};
	point_t bottomRight = { .row = bottomRightRow, .column = bottomRightColumn};
	
	taskStates[taskId] = (taskState_t){ .topLeft = topLeft, .bottomRight = bottomRight, .cursor = topLeft};
	
}

uint8_t printChar(char character, const struct format_t* format)
{
	uint8_t taskId = getCurrentTaskId(); //ver si se rompe justo cuando se interrumpio para cambiar
	if(taskStates[taskId].cursor.column > taskStates[taskId].bottomRight.column)
	{
		taskStates[taskId].cursor.column = taskStates[taskId].topLeft.column;
		taskStates[taskId].cursor.row++;
	}
	if(taskStates[taskId].cursor.row > taskStates[taskId].bottomRight.row)
	{
		return 1; //se paso de su pantalla
	}
	uint8_t * cursorPointer = pointToCursor(taskStates[taskId].cursor);
	*cursorPointer = character;
	*(cursorPointer+1) = format->backgroundColor << 4 | format->characterColor;
	taskStates[taskId].cursor.column++;
	return 0;
}

uint8_t print(const char * string, const struct format_t* format)
{
	int i;
	for (i = 0; string[i] != 0; i++)
	{
		int error = printChar(string[i], format);
		if(error)
			return 1;
	}
	return 0;
}

uint8_t newLine(color_t backgroundColor)
{
	uint8_t taskId = getCurrentTaskId();
	uint8_t currentRow = taskStates[taskId].cursor.row;
	format_t format = { .backgroundColor = backgroundColor, .characterColor = 0};
	while(taskStates[taskId].cursor.row == currentRow)
	{
		int error = printChar(' ', &format);
		if(error)
			return 1;
	}
	return 0;
}

void clearScreen(color_t backgroundColor)
{
	uint8_t taskId = getCurrentTaskId();
	for(int i = taskStates[taskId].topLeft.row ; i<= taskStates[taskId].bottomRight.row ; i++)
	{
		for(int j = taskStates[taskId].topLeft.column ; j<= taskStates[taskId].bottomRight.column ; j++)
		{
			point_t currentPoint = {.row = i, .column = j};
			uint8_t * cursorPointer = pointToCursor(currentPoint);
			*cursorPointer = ' ';
			*(cursorPointer+1) = backgroundColor << 4;
		}
	}
	taskStates[taskId].cursor = taskStates[taskId].topLeft;
}



