#include "_common.h"
#include "command.h"
#include "commands_system.h"
#include "commands_game.h"

// later separate to game_cmd.c etc.

#define DECL_COMMAND_STRING(unused1, str, unused2) str,
char far* command_strings[NUM_COMMANDS] =
{
    FOR_EACH_COMMAND(DECL_COMMAND_STRING)
};
#undef DECL_COMMAND_STRING

#define INSERT_COMMAND_FNP(unused1, unused2, func) func,
fnp_cmd command_functions[NUM_COMMANDS] =
{
    FOR_EACH_COMMAND(INSERT_COMMAND_FNP)
};
#undef INSERT_COMMAND_FNP

void execCommand(CommandEvent_t cmd)
{
    command_functions[cmd.event.id](cmd);
}
