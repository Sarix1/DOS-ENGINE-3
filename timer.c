#include <stdio.h>
#include <dos.h>
#include "common.h"
#include "timer.h"
#include "maths2.h"

Timer_t g_Timer = {0};

static void interrupt (far* old_Timer)(void) = NULL;

static void interrupt far Timer(void)
{
    static time_t last_clock_time = 0;
    //static time_t last_second;

    ++g_Timer.time;

    // keeps the PC clock ticking in the background
    // 1000ms/18.2hz = ~55ms
    if (last_clock_time + g_Timer.clock_interval < g_Timer.time)
    {
        last_clock_time = g_Timer.time;
        old_Timer();
    }

    if (g_Timer.last_sec + CLOCK_RATE < g_Timer.time)
    {
        g_Timer.last_sec += CLOCK_RATE;
        g_Timer.seconds++;

        // FPS calculation; optional for debugging
        g_Timer.fps_avg = toFixp(g_Timer.frames) / (g_Timer.seconds);
        g_Timer.fps = g_Timer.fps_count;
        g_Timer.fps_count = 0;
    }
}

static void setTimer(uint16_t new_count)
{
    asm cli
    outportb(CONTROL_8253, CONTROL_WORD);
    outportb(COUNTER_0, LOW_BYTE(new_count));
    outportb(COUNTER_0, HIGH_BYTE(new_count));
    asm sti
}

int quitTimer()
{
    asm cli
    setvect(TIME_KEEPER_INT, old_Timer);
    setTimer(TIMER_18HZ);
    asm sti

    return SUCCESS;
}

int initTimer()
{
    time_t t;
    int status;
    char str[10];

    g_Timer.time    = 0;
    g_Timer.seconds = 0;
    g_Timer.ticks   = 0;
    g_Timer.frames  = 0;

    g_Timer.tick_rate  = TICK_RATE;
    g_Timer.frame_rate = FRAME_RATE;

    g_Timer.tick_interval  = CLOCK_RATE/TICK_RATE;
    g_Timer.frame_interval = CLOCK_RATE/FRAME_RATE;
    g_Timer.clock_interval = (CLOCK_RATE*10 + OLD_CLK_RATE_10X/2) / OLD_CLK_RATE_10X;

    g_Timer.last_sec    = 0;
    g_Timer.last_tick   = 0;
    g_Timer.last_frame  = 0;
    g_Timer.last_cycle  = 0;

    g_Timer.fps     = 0;
    g_Timer.fps_avg = 0;

    //timer
    asm cli
    old_Timer = getvect(TIME_KEEPER_INT);
    setvect(TIME_KEEPER_INT, &Timer);
    setTimer(TIMER_1000HZ);
    asm sti

    // I suspect delay causes the interrupts to slow down, 
    // so the error checking code below always reports TIMER_SLOW

    /*
    t = getTime();
    delay(CLOCK_RATE);
    t = getTime()-t;
    sprintf(str, "%ld", t);
    message("\nTimer runs at: ", str, " Hz,\nExpected value: CLOCK_RATE Hz\n");
    
    if (t == 0)
        return ERROR_TIMER_FROZEN;
    if (t < CLOCK_RATE+CLOCK_RATE/10)
        return ERROR_TIMER_SLOW;
    if (t > CLOCK_RATE+CLOCK_RATE/10)
        return ERROR_TIMER_FAST;
    */

    return SUCCESS;
}
