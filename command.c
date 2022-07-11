#include "common.h"
#include "command.h"
#include "cmd_sys.h"
#include "cmd_game.h"

// later separate to game_cmd.c etc.

#define DECL_COMMAND_STRING(unused1, str, unused2) str,
char far* command_strings[NUM_COMMANDS] =
{
    FOR_EACH_COMMAND(DECL_COMMAND_STRING)
};
#undef DECL_COMMAND_STRING

#define INSERT_COMMAND_FNP(unused1, unused2, func) func,
fnp_ev command_functions[NUM_COMMANDS] =
{
    FOR_EACH_COMMAND(INSERT_COMMAND_FNP)
};
#undef INSERT_COMMAND_FNP

void execCommand(Event_t cmd)
{
    command_functions[cmd.event.id](cmd);
}
