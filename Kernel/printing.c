#include <printing.h>

static uint8_t * const video = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;

static screenState_t screenStates[MAX_SCREEN_COUNT];
static uint8_t currentScreenCount;

static uint8_t* pointToCursor(point_t point)
{
	return (uint8_t*)(video + 2*(point.row * width + point.column));
}

int8_t addScreenState(uint8_t topLeftRow, uint8_t topLeftColumn, uint8_t bottomRightRow, uint8_t bottomRightColumn)
{
	int8_t screenId = currentScreenCount++;
	if(screenId >= MAX_TASK_COUNT)
		return -1;
	
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
	
	screenStates[screenId] = (screenState_t){ .topLeft = topLeft, .bottomRight = bottomRight, .cursor = topLeft};
	return screenId;
}

uint8_t printChar(char character, const struct format_t* format)
{
	uint8_t screenId = getCurrentScreenId(); //ver si se rompe justo cuando se interrumpio para cambiar
	if(screenStates[screenId].cursor.column > screenStates[screenId].bottomRight.column)
	{
		screenStates[screenId].cursor.column = screenStates[screenId].topLeft.column;
		screenStates[screenId].cursor.row++;
	}
	if(screenStates[screenId].cursor.row > screenStates[screenId].bottomRight.row)
	{
		return 1; //se paso de su pantalla
	}
	uint8_t * cursorPointer = pointToCursor(screenStates[screenId].cursor);
	*cursorPointer = character;
	*(cursorPointer+1) = format->backgroundColor << 4 | format->characterColor;
	screenStates[screenId].cursor.column++;
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
	uint8_t screenId = getCurrentScreenId();
	uint8_t currentRow = screenStates[screenId].cursor.row;
	format_t format = { .backgroundColor = backgroundColor, .characterColor = 0};
	while(screenStates[screenId].cursor.row == currentRow)
	{
		int error = printChar(' ', &format);
		if(error)
			return 1;
	}
	return 0;
}

void clearScreen(color_t backgroundColor)
{
	uint8_t screenId = getCurrentScreenId();
	for(int i = screenStates[screenId].topLeft.row ; i<= screenStates[screenId].bottomRight.row ; i++)
	{
		for(int j = screenStates[screenId].topLeft.column ; j<= screenStates[screenId].bottomRight.column ; j++)
		{
			point_t currentPoint = {.row = i, .column = j};
			uint8_t * cursorPointer = pointToCursor(currentPoint);
			*cursorPointer = ' ';
			*(cursorPointer+1) = backgroundColor << 4;
		}
	}
	screenStates[screenId].cursor = screenStates[screenId].topLeft;
}

void getCursor(struct point_t* cursor)
{
	uint8_t screenId = getCurrentScreenId();
	cursor->row = screenStates[screenId].cursor.row;
	cursor->column = screenStates[screenId].cursor.column;
}

void setCursor(const struct point_t* cursor)
{
	uint8_t screenId = getCurrentScreenId();
	screenStates[screenId].cursor.row = cursor->row;
	screenStates[screenId].cursor.column = cursor->column;
}

void scrollUp(uint8_t rows){
	if(rows>24){
		return;
	}
	uint8_t screenId = getCurrentScreenId();
	for(int i = screenStates[screenId].topLeft.row +rows ; i<= screenStates[screenId].bottomRight.row ; i++)
	{
		for(int j = screenStates[screenId].topLeft.column ; j<= screenStates[screenId].bottomRight.column ; j++)
		{
			point_t currentPoint = {.row = i, .column = j}; //quizás sea mejor sacarlo afuera de los for por estilo?
			uint8_t * cursorPointer = pointToCursor(currentPoint);
			uint8_t * cursorPointerRowUp = cursorPointer-160*rows;
			*(cursorPointerRowUp) = *(cursorPointer);
		}
	}
}


