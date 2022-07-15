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

inline time_t getSeconds()
{
    return g_Timer.seconds;
}

inline time_t getTick()
{
    return g_Timer.ticks;
}

int initTimer();
int quitTimer();

#endif/* TIMER_H */
