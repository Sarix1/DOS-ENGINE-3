#ifndef STAT_DEF_H
#define STAT_DEF_H

#include "common.h"

#define STATE_IS_INIT       BIT_0
#define STATE_ENABLE_INPUT  BIT_1
#define STATE_ENABLE_UPDATE BIT_2
#define STATE_ENABLE_DRAW   BIT_3
#define STATE_ENABLE_AUDIO  BIT_4
#define STATE_FLAGS_ALL     (STATE_IS_INIT|STATE_ENABLE_INPUT|STATE_ENABLE_UPDATE|STATE_ENABLE_DRAW|STATE_ENABLE_AUDIO)

enum STATES
{
    STATE_CONSOLE,
    STATE_GAME,
    NUM_STATES
};

#endif/* STAT_DEF_H */
