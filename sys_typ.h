#ifndef SYS_TYP_H
#define SYS_TYP_H

#include "common.h"

typedef struct
{
    flags_t init_flags;
    flags_t print_flags;
    bool running : 1;
} System_t;

#endif/* SYS_TYP_H */
