#include "common.h"

#if DEBUG_INFO == 1

#include "debug.h"
#include "timer.h"
#include "maths2.h"

char debug[NUM_DEBUG][DEBUG_STR_LEN];

// there should instead be a displaystats function, which just reads the stats from the timer
// instead of sprintf every time this is called
void updateStats()
{
    sprintf(debug[DEBUG_FPS],
        "Time: %ld Minutes, %ld Seconds\nTicks: %ld, Frames: %ld\nFPS: %d, Avg. FPS: %d.%d",
        g_Timer.seconds/60, g_Timer.seconds%60, g_Timer.ticks, g_Timer.frames, g_Timer.fps,
        fixpWholeToDec(g_Timer.fps_avg), fixpFracToDec(g_Timer.fps_avg));
}

#include "draw_txt.h"

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
