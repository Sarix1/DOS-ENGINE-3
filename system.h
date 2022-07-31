#ifndef SYSTEM_H
#define SYSTEM_H

#include "system_defines.h"
#include "system_structs.h"

extern System_t g_System;

inline int isSubSysInit(int sus)
{
    return !!(g_System.init_flags & BIT(sus));
}

int init();
void quit();

#endif/* SYSTEM_H */
