#include "main.h"
//#include "text_output.h"
#include "input.h"
#include "action.h"
//#include "math_fixp_inline.h"
//#include "gfx_draw_inline.h"

extern controldata_t local_controldata; // temp

int main(void)
{
    init();
    
    pushState(STATE_GAME);
    //pushState(STATE_CONSOLE);

    while (g_System.running)
    {
        int i;

        handleInputEvents();
        // process tick(s)
        while (g_Timer.tick_simulated < g_Timer.tick_real)
        {
            updateStates();
            if (g_Timer.enable_ticks)
            {
                g_Timer.tick_simulated++;
                g_Timer.ticks_per_frame++;
            }
            else break;
        }


        // render frame
        if (g_Timer.time >= g_Timer.next_frame)
        {
            g_Timer.next_frame += g_Timer.frame_interval;

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
            g_Timer.ticks_per_frame = 0;
        }
    }

    quit();

    return 0;
}