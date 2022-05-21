#ifndef USERLIB_H
#define USERLIB_H


int strToNum(const unsigned char* str);
char strLength(const unsigned char* str);
char strPrefix(const unsigned char* prefix, const unsigned char*str);
int strCmp(const unsigned char* str1,const unsigned char* str2);
void printNormal(char * str);
int putChar(char c);
void printWithFormat(char* format,...);
char *convert(unsigned int num, int base);

#endif
