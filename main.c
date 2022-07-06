#include <stdio.h>
#include "common.h"
#include "main.h"
#include "system.h"
#include "timer.h"
#include "state.h"
#include "message.h"

#if DEBUG == 1
void updateStats() // there should instead be a displaystats function, which just reads the stats from the timer
{
    int32_t fraxx = 1+ ((int64_t)(g_Timer.fps_avg & 0xFFFF)*1000)/0xFFFF;
    sprintf(debug[DEBUG_FPS],
        "Time: %ld Minutes, %ld Seconds\nTicks: %ld, Frames: %ld\nFPS: %d, Avg. FPS: %ld.%ld",
        g_Timer.seconds/60, g_Timer.seconds%60, g_Timer.ticks, g_Timer.frames, g_Timer.fps, g_Timer.fps_avg >> 16, fraxx);
}                                                                                            
#endif

int main(void)
{
    init();
    
    pushState(STATE_GAME);

    while (g_System.running)
    {
        int i;
        g_Timer.last_cycle = g_Timer.time;
        // process tick(s)
        while (g_Timer.tick_accumulator >= g_Timer.tick_interval)
        {
            g_Timer.last_tick = g_Timer.time; // not used
            input();
            updateStates();
            g_Timer.ticks++;
            g_Timer.tick_accumulator -= g_Timer.tick_interval;
        }
        // render frame
        if (g_Timer.last_frame + g_Timer.frame_interval < g_Timer.time)
        {
            g_Timer.last_frame = g_Timer.time;
            drawStates();
            render();
            g_Timer.frames++;
            g_Timer.fps_count++;
            #if DEBUG == 1
            updateStats();
            #endif
        }
        g_Timer.tick_accumulator += g_Timer.time - g_Timer.last_cycle;
    }

    quit();

    return 0;
}