#include <stdio.h>
#include <dos.h>
#include "_common.h"
#include "timer.h"
#include "math_fixp_inline.h"

Timer_t g_Timer = {0};

static void interrupt (far* old_Timer_ISR)(void) = NULL;

static void interrupt far Timer_ISR(void)
{
    ++g_Timer.time;

    // keeps the PC clock ticking in the background
    // 1000ms/18.2hz = ~55ms
    if (g_Timer.time >= g_Timer.next_clock)
    {
        g_Timer.next_clock += g_Timer.clock_interval;
        old_Timer_ISR();
    }

    if (g_Timer.enable_ticks && g_Timer.time >= g_Timer.next_tick)
    {
        g_Timer.next_tick += g_Timer.tick_interval;
        g_Timer.tick_real++;
    }

    if (g_Timer.time >= g_Timer.next_sec)
    {
        static int sec_index = 0;
        static int avg_fps_accumulator = 0;

        g_Timer.next_sec += CLOCK_RATE;
        g_Timer.seconds++;

        // FPS calculation; optional for debugging
        g_Timer.fps = g_Timer.fps_count;
        g_Timer.fps_count = 0;
        g_Timer.fps_last10[sec_index++] = g_Timer.fps;
        if (sec_index == 11) sec_index = 0;
        avg_fps_accumulator += g_Timer.fps;
        avg_fps_accumulator -= g_Timer.fps_last10[sec_index];
        g_Timer.fps_avg = toFixp(avg_fps_accumulator)/10;
    }
}

static void setTimer(uint16_t new_count)
{
    asm cli;
    outportb(CONTROL_8253, CONTROL_WORD);
    outportb(COUNTER_0, LOW_BYTE(new_count));
    outportb(COUNTER_0, HIGH_BYTE(new_count));
    asm sti;
}

int quitTimer()
{
    asm cli;
    setvect(TIME_KEEPER_INT, old_Timer_ISR);
    setTimer(TIMER_18HZ);
    asm sti;

    return SUCCESS;
}

int initTimer()
{
    time_t t;
    int status;
    char str[10];

    g_Timer.time            = 0;
    g_Timer.seconds         = 0;
    g_Timer.tick_real = 0;
    g_Timer.tick_simulated  = 0;
    g_Timer.frames          = 0;

    g_Timer.tick_rate       = TICK_RATE;
    g_Timer.frame_rate      = FRAME_RATE;

    g_Timer.tick_interval   = CLOCK_RATE/TICK_RATE;
    g_Timer.frame_interval  = CLOCK_RATE/FRAME_RATE;
    g_Timer.clock_interval  = (CLOCK_RATE*10 + OLD_CLK_RATE_10X/2) / OLD_CLK_RATE_10X;

    g_Timer.next_sec        = 0;
    g_Timer.next_tick       = 0;
    g_Timer.next_frame      = 0;

    g_Timer.fps             = 0;
    g_Timer.fps_avg         = 0;

    //timer
    asm cli;
    old_Timer_ISR = getvect(TIME_KEEPER_INT);
    setvect(TIME_KEEPER_INT, &Timer_ISR);
    setTimer(TIMER_1000HZ);
    asm sti;

    // I suspect delay causes the interrupts to slow down, 
    // so the error checking code below always reports TIMER_SLOW

    /*
    t = getTime();
    delay(CLOCK_RATE);
    t = getTime()-t;
    sprintf(str, "%ld", t);
    print(0, "\nTimer runs at: ", str, " Hz,\nExpected value: CLOCK_RATE Hz\n");
    
    if (t == 0)
        return ERROR_TIMER_FROZEN;
    if (t < CLOCK_RATE+CLOCK_RATE/10)
        return ERROR_TIMER_SLOW;
    if (t > CLOCK_RATE+CLOCK_RATE/10)
        return ERROR_TIMER_FAST;
    */

    return SUCCESS;
}
