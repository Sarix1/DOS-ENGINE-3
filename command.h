#ifndef COMMAND_H
#define COMMAND_H

#include "common.h"

#define FOR_EACH_COMMAND(DO) \
    DO(COMMAND_NULL,        "",             NULL) \
    DO(COMMAND_QUIT,        "quit",         cmdQuit) \
    DO(COMMAND_START_GAME,  "start_game",   cmdStartGame) \
    DO(COMMAND_SPAWN,       "spawn",        cmdSpawn) \

#define DEF_COMMAND_ENUM(cmd, unused1, unused2) cmd,
enum COMMANDS
{
    FOR_EACH_COMMAND(DEF_COMMAND_ENUM)
    NUM_COMMANDS
};
#undef DEF_COMMAND_ENUM

extern char far* command_strings[NUM_COMMANDS];

void execCommand(Event_t cmd);

#endif/* COMMAND_H */
