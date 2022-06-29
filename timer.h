#ifndef TIMER_H
#define TIMER_H

#include "common.h"
#include "time_typ.h"

extern Timer_t g_Timer;

inline time_t getTime()
{
    return g_Timer.time;
}

void initTimer();
void quitTimer();

#endif/* TIMER_H */
