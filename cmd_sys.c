#include "common.h"
#include "command.h"
#include "sys_main.h"
#include "state.h"

void cmdQuit(Event_t cmd)
{
    quit();
}

void cmdStartGame(Event_t cmd)
{
    popState();
    pushState(STATE_GAME);
}

/*
void cmdGoto(Event_t cmd)
{
    pushState(cmd.event.params.state.id);
}
*/