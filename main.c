#include "main.h"
#include "print.h"
#include "maths2.h"

int main(void)
{
    init();
    
    pushState(STATE_GAME);
    pushState(STATE_CONSOLE); 
    print(COLOR_CYAN, "Stuff: %ld\n", abs(FIXP_ONE));
    print(COLOR_CYAN, "Stuff: %ld\n", abs(-FIXP_ONE));

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
            #if DEBUG_INFO == 1
            drawDebug();
            #endif
            render();

            g_Timer.frames++;
            g_Timer.fps_count++;
            
            #if DEBUG_INFO == 1
            updateStats();
            #endif
        }
        g_Timer.tick_accumulator += g_Timer.time - g_Timer.last_cycle;
    }

    quit();

    return 0;
}