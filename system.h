#ifndef SYSTEM_H
#define SYSTEM_H

#include "sys_def.h"
#include "sys_typ.h"

extern System_t g_System;

inline int isSubSysInit(int sus)
{
    return !!(g_System.init_flags & BIT(sus));
}

#endif/* SYSTEM_H */
