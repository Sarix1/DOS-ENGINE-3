#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h>

enum PRINT_FLAGS
{
    PRINT_FLAG_STDOUT,
    PRINT_FLAG_STDERR,
    PRINT_FLAG_CONSOLE
};

void print(int color, char* format, ...);
void setPrintFlags(flags_t flags);
void printStatus(int status);
//void printFile(FILE* file, byte color);

#endif/* PRINT_H */
