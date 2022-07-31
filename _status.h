#ifndef STATUS_H
#define STATUS_H

#include "_macro.h"
#include "system_defines.h"

#define FOR_EACH_ERROR(DO) \
    DO(ERROR_ASSERT,        "Expression evaluated as false") \
    DO(ERROR_MEMORY,        "Memory allocation failure") \
    DO(ERROR_TIMER_FROZEN,  "Timer frozen") \
    DO(ERROR_TIMER_SLOW,    "Timer too slow") \
    DO(ERROR_TIMER_FAST,    "Timer too fast")

#define DEF_ERROR_ENUM(e, unused) e,
enum ERROR_CODES
{
    SUCCESS,
    ERROR,
    FOR_EACH_ERROR(DEF_ERROR_ENUM)
    NUM_ERRORS
};
#undef DEF_ERROR_ENUM

extern const char far* error_strings[NUM_ERRORS];

#define SUCCESS         0
#define ERROR           1

#define BUFFER_OK       0
#define BUFFER_FULL     1

#define YES             1
#define NO              0

#define ENABLED         1
#define DISABLED        0

#define INITIALIZED     1
#define UNINITIALIZED   0

#define HANDLED         1
#define NOT_HANDLED     0

#define NONE            0
#define AUTO           -1
#define DEFAULT        -2

#endif/* STATUS_H */
