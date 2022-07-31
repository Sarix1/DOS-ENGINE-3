#include "_common.h"
#include "_string.h"

#include "command.h"
#include "text_input.h"
#include "commands_system.h"
#include "commands_timer.h"
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

void execCommand(Command_t cmd)
{
    command_functions[cmd.data.id](cmd);
}

static Params_t getCommandToken(char* str, int len)
{
    Params_t info;
    id_t cmd_id;

    for (cmd_id = 0; cmd_id < NUM_COMMANDS; cmd_id++)
    {
        if ((info.cmd.str_offset = strcmptok(str, command_strings[cmd_id], ' ')) != -1)
        {
            info.cmd.id = cmd_id;
            return info;
        }
    }

    info.cmd.id = CMD_NONE;
    return info;
}

static Params_t getCommandArgs(id_t cmd_id, char* arg_str)
{
    Params_t args = {0};

    switch (cmd_id)
    {
    case CMD_SPAWN:
        sscanf(arg_str, "%d %d %d", &args.pos.x, &args.pos.y, &args.pos.var.angle);
        break;
    case CMD_ACTION_DELAY:
        sscanf(arg_str, "%d", &args.vars.a);
        break;
    }

    return args;
}

Command_t parseCommand(char* str, int length)
{
    Command_t cmd;
    Params_t info = getCommandToken(str, length);
    cmd.data.id = info.cmd.id;
// currently broken, unable to fetch arguments
// depending on no arguments/some arguments, either set/get is called from fnp list
    if (info.cmd.id != CMD_NONE)
        cmd.data.params = getCommandArgs(info.cmd.id, str + info.cmd.str_offset);

    return cmd;
}