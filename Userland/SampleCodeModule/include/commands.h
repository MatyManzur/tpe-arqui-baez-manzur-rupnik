#ifndef COMMANDS_H
#define COMMANDS_H

#include <userlib.h>
#include <syslib.h>


void printRegisters(uint8_t argc, void** argv);
void help(uint8_t argc, void** argv);
void time(uint8_t argc, void** argv);
void clear(uint8_t argc, void** argv);
void printmem(uint8_t argc, void** argv);

#endif
