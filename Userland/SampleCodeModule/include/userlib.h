#ifndef USERLIB_H
#define USERLIB_H

#include <syslib.h>
#include <stdarg.h>



int strToNum(const unsigned char* str);
char strLength(const unsigned char* str);
uint8_t strPrefix(const unsigned char*prefix, const unsigned char*str, unsigned char** afterPrefix);
int strCmp(const unsigned char* str1,const unsigned char* str2);
void setColor(color_t backgroundColor, color_t characterColor);
void printString(unsigned char * str);
void printStringColor(unsigned char * str, color_t backgroundColor, color_t characterColor);
void putChar(unsigned char c);
void putCharColor(unsigned char c, color_t backgroundColor, color_t characterColor);
void printWithFormat(char* format,...);
char *convert(unsigned int num, int base, unsigned int minDigitCount);
uint8_t ulongToStr(unsigned long num, char* ans);
uint8_t strCopy(char* source, char* dest);
int parser(char* string, char** buffer,char separator,int maxTokenCount,int maxTokenLenght);
int xtou64(const char *str, uint64_t* ans);
void newLine();

#endif
