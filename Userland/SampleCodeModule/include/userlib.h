#ifndef USERLIB_H
#define USERLIB_H

#include <syslib.h>
#include <stdarg.h>

int strToNum(const unsigned char* str);
char strLength(const unsigned char* str);
char strPrefix(const unsigned char* prefix, const unsigned char*str);
int strCmp(const unsigned char* str1,const unsigned char* str2);
void printString(char * str);
void printStringColor(char * str, color_t backgroundColor, color_t characterColor);
void putChar(char c);
void putCharColor(char c, color_t backgroundColor, color_t characterColor);
void printWithFormat(char* format,...);
char *convert(unsigned int num, int base);

#endif
