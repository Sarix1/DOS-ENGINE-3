#ifndef TIMER_H
#define TIMER_H

#include "_common.h"
#include "timer_defines.h"
#include "timer_structs.h"

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
    return g_Timer.tick_simulated;
}

inline time_t getTickReal()
{
    return g_Timer.tick_real;
}


int initTimer();
int quitTimer();

#endif/* TIMER_H */
