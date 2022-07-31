#ifndef COMMAND_H
#define COMMAND_H

#include "command_defines.h"
#include "command_structs.h"

Command_t parseCommand(char* str, int length);
void      execCommand (Command_t cmd);

#endif/* COMMAND_H */
