#ifndef CONSOLE_H
#define CONSOLE_H

#include "common.h"
#include "txt_def.h"
#include "txt_typ.h"

#define CONSOLE_BUFFER_SIZE 80
#define CONSOLE_INPUT_SIZE  256
#define CONSOLE_MAX_LINES   64
#define CONSOLE_VIS_LINES   24

extern Log_t g_ConsoleLog;

void consoleInput(InputField_t* input);
void printConsole(byte color, char* format, ...);
void printStderrConsole(byte color, char* format, ...);

#endif/* CONSOLE_H */