#include "_common.h"
#include "command_structs.h"
#include "system.h"
#include "state.h"

void cmdQuit(CommandEvent_t cmd)
{
    quit();
}

void cmdStartGame(CommandEvent_t cmd)
{
    popState();
    pushState(STATE_GAME);
}

/*
void cmdGoto(CommandEvent_t cmd)
{
    pushState(cmd.event.params.state.id);
}
*/