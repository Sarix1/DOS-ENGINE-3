#include "common.h"
#include "state.h"

int initConsole();
int quitConsole();
void enterConsole();
void leaveConsole();
void updateConsole();
void drawConsole();

int initGame();
int quitGame();
void enterGame();
void leaveGame();
void updateGame();
void drawGame();

void nothing() {;}

StateManager_t g_StateMgr = {0};

State_t States[NUM_STATES] =
{
    {
        STATE_CONSOLE, 0,
        initConsole,
        quitConsole,
        enterConsole,
        leaveConsole,
        updateConsole,
        drawConsole
    },
    {
        STATE_GAME, 0,
        initGame,
        quitGame,
        enterGame,
        leaveGame,
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

int pushState(id_t new)
{
    if (States[new].flags & STATE_IS_INIT)
    {
        if (getTopState() == new)
            return 0;
        // if it's not the top state, make it
        else
        {
            int i = 0;
            id_t old = getTopState();
            States[old].leave();

            while (g_StateMgr.Stack[i]->id != new) i++;
            while (i < g_StateMgr.state_count-1)
                g_StateMgr.Stack[i] = g_StateMgr.Stack[++i];
            g_StateMgr.Stack[i] = &States[new];

            States[new].enter();
        }
    }
    else
    {
        if (g_StateMgr.state_count > 0)
        {
            id_t old = getTopState();
            States[old].leave();
        }
        
        g_StateMgr.state_count++;
        setTopState(new);

        States[new].flags = STATE_FLAGS_ALL;
        States[new].init();
        States[new].enter();
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

    // state changes should occur here, not during state execution
    // queue an event {POP_STATE, id}, then execute that here
}

void drawStates()
{
    int i;
    for (i = 0; i < g_StateMgr.state_count; i++)
    if (g_StateMgr.Stack[i]->flags & STATE_ENABLE_DRAW)
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

#include "input.h"

int handleGlobalKeys(InputEvent_t event)
{
    if (event.type == KEYSTATE_RELEASED)
        return NOT_HANDLED;

    switch (event.keycode)
    {
    case KEY_ESC:
        popState();
        return HANDLED;
    case KEY_F1:
        pushState(STATE_CONSOLE);
        return HANDLED;
    default:
        return NOT_HANDLED;
    }

    return NOT_HANDLED;
}