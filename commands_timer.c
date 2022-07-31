#include "_common.h"
#include "command_structs.h"
#include "timer.h"
#include "text_output.h"

void cmdSetActionDelay(Command_t cmd)
{
    g_Timer.action_delay = cmd.data.params.vars.a;
}

void cmdGetActionDelay(Command_t unused)
{
    print(DEFAULT, "%d\n", g_Timer.action_delay);
}