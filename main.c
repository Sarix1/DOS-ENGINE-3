#include <stdio.h>
#include "common.h"
#include "system.h"
#include "timer.h"
#include "maths2.h"

#if DEBUG == 1
void updateStats()
{
    sprintf(debug[DEBUG_FPS],
        "Time: %ld Minutes, %ld Seconds\nTicks: %ld, Frames: %ld\nFPS: %d, Avg. FPS: %d",
        g_Timer.seconds/60, g_Timer.seconds%60, g_Timer.ticks, g_Timer.frames, g_Timer.fps, -1);
}
#endif

int main(void)
{
    time_t last_time   = 0; // Used for accumulating seconds & FPS calculation
    time_t last_tick   = 0; // Tracks time elapsed since last tick started
    time_t last_frame  = 0; // Tracks time elapsed since last draw started
    time_t accumulator = 0; // Incremented by frame draw duration, decremented by ticks
    int frame_count    = 0; // Counts frames in a second so far; used by debug

    init();

    while (1)
    {  

        if (last_tick + g_Timer.tick_time < g_Timer.time) // tick
        {
            do
            {
                last_tick = g_Timer.time;

                input();  
                physics();

                accumulator -= g_Timer.tick_time;
                g_Timer.ticks++;
            }
            while (accumulator >= g_Timer.tick_time);
        }

        if (last_frame + g_Timer.frame_time < g_Timer.time) // frame
        {
            last_frame = g_Timer.time;

            draw();
            render();

            g_Timer.frames++;
            frame_count++;
            accumulator += g_Timer.time - last_frame;

            #if DEBUG == 1
            updateStats();
            #endif
        }

        if (last_time + 1000 < g_Timer.time) // FPS calculation; optional for debugging
        {
            last_time += 1000;
            g_Timer.seconds++;
            g_Timer.fps_avg = toFixp(g_Timer.frames) / g_Timer.seconds;
            g_Timer.fps = frame_count;
            frame_count = 0;
        }
    }

    quit();

    return 0;
}