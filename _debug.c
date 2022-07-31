#include "_common.h"

#if DEBUG_INFO == 1

#include "_debug.h"
#include "timer.h"
#include "math_fixp_inline.h"

char debug[NUM_DEBUG][DEBUG_STR_LEN];

// there should instead be a displaystats function, which just reads the stats from the timer
// instead of sprintf every time this is called
void updateStats()
{
    sprintf(debug[DEBUG_FPS],
        "Time: %ld mins, %ld secs\n"
        "Tics(game): %ld, Tics(real): %ld\n"
        "Frames: %ld, FPS: %d, Avg: %s",

        g_Timer.seconds/60, g_Timer.seconds%60,
        g_Timer.tick_simulated, g_Timer.tick_real,
        g_Timer.frames, g_Timer.fps, fixpStr(g_Timer.fps_avg)
    );
}

#include "gfx_draw_text.h"

void drawDebug()
{
    int i;
    int y = 0;

    for (i = 0; i < NUM_DEBUG; i++)
    {
        if (debug[i][0] != '\0')
            y += ((drawText(0, y, 0, 0, debug[i], COLOR_DEBUG_TEXT) + 1) << 3);
    }
}

#endif
