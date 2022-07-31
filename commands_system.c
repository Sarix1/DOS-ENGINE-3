#include "_common.h"
#include "command_structs.h"
#include "system.h"
#include "state.h"

void cmdQuit(Command_t cmd)
{
    quit();
}

void cmdStartGame(Command_t cmd)
{
    popState();
    pushState(STATE_GAME);
}

/*
void cmdGoto(Command_t cmd)
{
    pushState(cmd.data.params.state.id);
}
*/