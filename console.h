#ifndef CONSOLE_H
#define CONSOLE_H

#include "_common.h"
#include "text_defines.h"
#include "text_structs.h"

#define CONSOLE_BUFFER_SIZE 1024
#define CONSOLE_INPUT_SIZE  256
#define CONSOLE_MAX_LINES   64
#define CONSOLE_VIS_LINES   16

void consoleInput(TextInput_t* input);
void printConsole(byte color, char* format, ...);

#endif/* CONSOLE_H */
