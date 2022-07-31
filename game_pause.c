#include "_common.h"
#include "timer.h"
#include "state.h"
#include "input.h"

void togglePause()
{
    if (getStateFlags(STATE_PAUSE) & STATE_FLAG_ACTIVE)
    {
        removeState(STATE_PAUSE);
    }
    else if (getStateFlags(STATE_GAME) & STATE_FLAG_ACTIVE)
    {
        pushState(STATE_GAME);
        pushState(STATE_PAUSE);
    }
}

int pauseInit()
{
    clearStateFlags(STATE_GAME, STATE_FLAG_UPDATE);
    g_Timer.enable_ticks = 0;

    return 0;
}

int pauseQuit()
{
    setStateFlags(STATE_GAME, STATE_FLAG_UPDATE);
    g_Timer.enable_ticks = 1;

    return 0;
}

void pauseEsc()
{
    removeState(STATE_PAUSE);
}
