#ifndef PRINTING_H
#define PRINTING_H

#include <stdint.h>
#include <scheduler.h>

typedef enum color_t {BLACK=0,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,L_GRAY,D_GRAY,L_BLUE,L_GREEN,L_CYAN,L_RED,PINK,YELLOW,WHITE} color_t;

typedef struct format_t
{
	color_t backgroundColor;
	color_t characterColor;
} format_t;

//Para ser llamada desde el scheduler
void addTaskState(uint8_t taskId, uint8_t topLeftRow, uint8_t topLeftColumn, uint8_t bottomRightRow, uint8_t bottomRightColumn);

//syscalls
uint8_t printChar(char character, const struct format_t* format);
uint8_t print(const char * string, const struct format_t* format);
uint8_t newLine(color_t backgroundColor);
void clearScreen(color_t backgroundColor);

#endif
