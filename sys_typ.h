#ifndef SYS_TYP_H
#define SYS_TYP_H

#include "common.h"

enum SYSTEM_TYPES
{
    SYS_VIDEO,
    SYS_INPUT,
    SYS_TIMER,
    //SYS_AUDIO,
    SYS_GAME,
    NUM_SYSTEMS
};

typedef struct
{
    bool running : 1;
    bool init[NUM_SYSTEMS];
} System_t;

extern System_t g_System;
extern const char far* system_str[NUM_SYSTEMS];

inline int isInit(int sus)
{
    return g_System.init[sus];
}

#endif/* SYS_TYP_H */
