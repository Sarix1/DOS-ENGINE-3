#ifndef TIMER_H
#define TIMER_H

#include "common.h"
#include "time_def.h"
#include "time_typ.h"

extern Timer_t g_Timer;

inline time_t getTime()
{
    return g_Timer.time;
}

int initTimer();
int quitTimer();

#endif/* TIMER_H */
