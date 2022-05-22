#ifndef PRINTING_H
#define PRINTING_H

#include <stdint.h>
#include <scheduler.h>

#define MAX_SCREEN_COUNT 16

typedef enum color_t {BLACK=0,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,L_GRAY,D_GRAY,L_BLUE,L_GREEN,L_CYAN,L_RED,PINK,YELLOW,WHITE} color_t;

typedef struct format_t
{
	color_t backgroundColor;
	color_t characterColor;
} format_t;
typedef struct point_t
{
	uint8_t row;
	uint8_t column;
} point_t;

typedef struct screenState_t
{
	point_t topLeft;
	point_t bottomRight;
	point_t cursor;
} screenState_t;

//Para ser llamada desde el scheduler
int8_t addScreenState(uint8_t topLeftRow, uint8_t topLeftColumn, uint8_t bottomRightRow, uint8_t bottomRightColumn);

//syscalls
uint8_t printChar(char character, const struct format_t* format);
uint8_t print(const char * string, const struct format_t* format);
uint8_t newLine(color_t backgroundColor);
void clearScreen(color_t backgroundColor);
void getCursor(struct point_t* cursor);
void setCursor(const struct point_t* cursor);
void scrollUp(uint8_t rows);

#endif
