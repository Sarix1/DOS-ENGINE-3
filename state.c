#include "common.h"
#include "state.h"

int initGame();
int quitGame();
void updateGame();
void drawGame();
void nothing() {;}

StateManager_t g_StateMgr = {0};

State_t States[NUM_STATES] =
{
    {
        STATE_GAME, 0,
        initGame,
        quitGame,
        nothing,
        nothing,
        updateGame,
        drawGame
    },
};

int initStateMgr()
{
    return SUCCESS;
}

int quitStateMgr()
{
    return SUCCESS;
}

inline id_t getTopState()
{
    return g_StateMgr.Stack[g_StateMgr.state_count-1]->id;
}

inline void setTopState(id_t id)
{
    g_StateMgr.Stack[g_StateMgr.state_count-1] = &States[id];
}

int pushState(id_t new_)
{
    // to do: if it's not the top state, make it
    if (States[new_].flags & STATE_IS_INIT)
        return 0;
    else
    {
        if (g_StateMgr.state_count > 0)
        {
            id_t old = getTopState();
            States[old].leave();
        }
        
        g_StateMgr.state_count++;
        setTopState(new_);

        States[new_].flags = STATE_FLAGS_ALL;
        States[new_].init();
        States[new_].enter();
    }
    return 0;
}

int popState()
{
    if (g_StateMgr.state_count == 0)
        return 0;
    else
    {
        id_t old = getTopState();
        g_StateMgr.state_count--;

        States[old].flags = 0;
        States[old].leave();
        States[old].quit();

        if (g_StateMgr.state_count > 0)
        {
            id_t new_ = getTopState();
            States[new_].enter();
        }
    }
    return 0;
}

void updateStates()
{
    int i;
    for (i = 0; i < g_StateMgr.state_count; i++)
        if (g_StateMgr.Stack[i]->flags & STATE_ENABLE_UPDATE)
            g_StateMgr.Stack[i]->update();
}

void drawStates()
{
    int i;
    for (i = 0; i < g_StateMgr.state_count; i++)
    if (g_StateMgr.Stack[i]->flags & STATE_ENABLE_DRAW)
        g_StateMgr.Stack[i]->draw();
}
