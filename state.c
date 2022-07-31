#include "_common.h"
#include "state.h"
#include "timer.h"

int  consoleInit();
int  consoleQuit();
void consoleEnter();
void consoleLeave();
void consoleUpdate();
void consoleDraw();
void consoleEsc();

int  gameInit();
int  gameQuit();
void gameEnter();
void gameLeave();
void gameUpdate();
void gameDraw();
void gameEsc();

int  pauseInit();
int  pauseQuit();
void pauseDraw();
void pauseEsc();

static void nothing() {;}

StateManager_t g_StateMgr = {0};

State_t States[NUM_STATES] =
{
    {
        STATE_CONSOLE, 0,
        consoleInit,
        consoleQuit,
        consoleEnter,
        consoleLeave,
        consoleUpdate,
        consoleDraw,
        consoleEsc,
    },
    {
        STATE_GAME, 0,
        gameInit,
        gameQuit,
        gameEnter,
        gameLeave,
        gameUpdate,
        gameDraw,
        gameEsc,
    },
    {
        STATE_PAUSE, 0,
        pauseInit,
        pauseQuit,
        nothing,
        nothing,
        nothing,
        pauseDraw,
        pauseEsc,
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

State_t* getState(id_t id)
{
    return &States[id];
}

State_t* getTopState()
{
    if (g_StateMgr.state_count > 0)
        return g_StateMgr.Stack[g_StateMgr.state_count-1];
    else
        return NULL;
}

static inline void setTopState(id_t id)
{
    g_StateMgr.Stack[g_StateMgr.state_count-1] = &States[id];
}

void moveStateToTop(id_t id)
{
    int i = 0;
    State_t* old = getTopState();
    old->leave();
    while (g_StateMgr.Stack[i]->id != id)
        i++;
    while (i < g_StateMgr.state_count-1)
        g_StateMgr.Stack[i] = g_StateMgr.Stack[++i];
    g_StateMgr.Stack[i] = &States[id];
    States[id].enter();
}

void pushState(id_t id)
{
    if (States[id].flags & STATE_FLAG_ACTIVE)
    {
        if (getTopState()->id == id)
            return;
        else
            moveStateToTop(id);
    }
    else
    {
        if (g_StateMgr.state_count > 0)
            getTopState()->leave();

        g_StateMgr.state_count++;
        setTopState(id);
        States[id].flags = STATE_FLAGS_ALL;
        States[id].init();
        States[id].enter();
    }
}

void popState()
{
    if (g_StateMgr.state_count == 0)
        return;
    else
    {
        State_t* old = getTopState();
        old->flags = 0;
        old->leave();
        old->quit();
        g_StateMgr.state_count--;
    }

    if (g_StateMgr.state_count > 0)
        getTopState()->enter();
}

void removeState(id_t id)
{
    if ((States[id].flags & STATE_FLAG_ACTIVE) == 0)
        return;
    else if (id == getTopState()->id)
    {
        popState();
        return;
    }
    else
    {
        int i = 0;
        while (g_StateMgr.Stack[i]->id != id)
            i++;
        while (i < g_StateMgr.state_count-1)
        {
            g_StateMgr.Stack[i] = g_StateMgr.Stack[1+i];
            i++;
        }
        g_StateMgr.state_count--;
        States[id].flags = 0;
        States[id].leave();
        States[id].quit();
    }
}

void updateStates()
{
    int i;
    for (i = 0; i < g_StateMgr.state_count; i++)
        if (g_StateMgr.Stack[i]->flags & STATE_FLAG_UPDATE)
            g_StateMgr.Stack[i]->update();

    // state changes should occur here, not during state execution
    // queue an event {POP_STATE, id}, then execute that here
}

void drawStates()
{
    int i;
    for (i = 0; i < g_StateMgr.state_count; i++)
        if (g_StateMgr.Stack[i]->flags & STATE_FLAG_DRAW)
            g_StateMgr.Stack[i]->draw();
}

void setStateFlags(id_t state, flags_t flags)
{
    States[state].flags |= flags;
}

void clearStateFlags(id_t state, flags_t flags)
{
    States[state].flags &= ~flags;
}

flags_t getStateFlags(id_t state)
{
    return States[state].flags;
}

void toggleConsole()
{
    if (getStateFlags(STATE_CONSOLE) & STATE_FLAG_ACTIVE)
        removeState(STATE_CONSOLE);
    else
        pushState(STATE_CONSOLE);
}
