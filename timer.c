#include <dos.h>
#include <conio.h>
#include "common.h"
#include "time_def.h"
#include "time_typ.h"

Timer_t g_Timer = {0};

static void interrupt (far* old_Timer)(void) = NULL;

static void interrupt far Timer(void)
{
    static time_t last_clock_time = 0;
    //static time_t last_second;

    ++g_Timer.time;

    // keeps the PC clock ticking in the background
    // 1000ms/18.2hz = ~55ms
    if (last_clock_time + 55 < g_Timer.time) 
    {
        last_clock_time = g_Timer.time;
        old_Timer();
    } 
}

void setTimer(uint16_t new_count)
{
    asm cli
    outportb(CONTROL_8253, CONTROL_WORD);
    outportb(COUNTER_0, LOW_BYTE(new_count));
    outportb(COUNTER_0, HIGH_BYTE(new_count));
    asm sti
}

void quitTimer()
{
    asm cli
    setvect(TIME_KEEPER_INT, old_Timer);
    setTimer(TIMER_18HZ);
    asm sti
}

void initTimer()
{
    g_Timer.running    = 1;
    g_Timer.time       = 0;
    g_Timer.seconds    = 0;
    g_Timer.ticks      = 0;
    g_Timer.frames     = 0;
    g_Timer.tick_time  = 1000/TICK_RATE;
    g_Timer.frame_time = 1000/FRAME_RATE;
    g_Timer.tick_rate  = TICK_RATE;
    g_Timer.frame_rate = FRAME_RATE;
    g_Timer.fps        = 0;
    g_Timer.fps_avg    = 0;

    //timer
    asm cli
    old_Timer = getvect(TIME_KEEPER_INT);
    setvect(TIME_KEEPER_INT, &Timer);
    setTimer(TIMER_1000HZ);
    asm sti
}
