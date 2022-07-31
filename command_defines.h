#ifndef CMD_DEF_H
#define CMD_DEF_H

#include "_common.h"
#include "command_structs.h"
#include "action_defines.h"

#define FOR_EACH_COMMAND(DO) \
    DO(CMD_QUIT,            "quit",             cmdQuit) \
    DO(CMD_START_GAME,      "start_game",       cmdStartGame) \
    DO(CMD_SPAWN,           "spawn",            cmdSpawn) \
    DO(CMD_ACTION_DELAY,    "action_delay",     cmdSetActionDelay) \

#define DEF_COMMAND_ENUM(cmd, unused1, unused2) cmd,
enum COMMANDS
{
    CMD_NONE = NUM_ACTIONS+1,
    FOR_EACH_COMMAND(DEF_COMMAND_ENUM)
    NUM_COMMANDS
};
#undef DEF_COMMAND_ENUM

extern char far* command_strings[NUM_COMMANDS];

void execCommand(Command_t cmd);

#endif/* CMD_DEF_H */
