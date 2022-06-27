#ifndef COMMAND_H
#define COMMAND_H

#include "common.h"

enum CONTROLS
{
    CTRL_FORWARD    = FLAG_0,
    CTRL_BACKWARD   = FLAG_1,
    CTRL_MOVE_UP    = FLAG_2,
    CTRL_MOVE_DOWN  = FLAG_3,
    CTRL_MOVE_LEFT  = FLAG_4,
    CTRL_MOVE_RIGHT = FLAG_5,
    CTRL_LOOK_UP    = FLAG_6,
    CTRL_LOOK_DOWN  = FLAG_7,
    CTRL_LOOK_LEFT  = FLAG_8,
    CTRL_LOOK_RIGHT = FLAG_9,
    CTRL_SPEED      = FLAG_10,
    CTRL_DUCK       = FLAG_11,
    CTRL_JUMP       = FLAG_12,
    CTRL_DIVE       = FLAG_13,
    CTRL_NEXT       = FLAG_14,
    CTRL_PREV       = FLAG_15,
    CTRL_USE        = FLAG_16,
    CTRL_DROP       = FLAG_17,
    CTRL_RELOAD     = FLAG_18,
    CTRL_ATTACK1    = FLAG_19,
    CTRL_ATTACK2    = FLAG_20,
    CTRL_ATTACK3    = FLAG_21,
    CTRL_ATTACK4    = FLAG_22
};

enum COMMANDS
{
    CMD_FORWARD,
    CMD_BACKWARD,
    CMD_MOVE_UP,
    CMD_MOVE_DOWN,
    CMD_MOVE_LEFT,
    CMD_MOVE_RIGHT,
    CMD_LOOK_UP,
    CMD_LOOK_DOWN,
    CMD_LOOK_LEFT,
    CMD_LOOK_RIGHT,
    CMD_SPEED,
    CMD_DUCK,
    CMD_JUMP,
    CMD_DIVE,
    CMD_NEXT,
    CMD_PREV,
    CMD_USE,
    CMD_DROP,
    CMD_RELOAD,
    CMD_ATTACK1,
    CMD_ATTACK2,
    CMD_ATTACK3,
    CMD_ATTACK4, 
    CMD_EXIT
};

typedef union
{
    struct
    {
        id_t player_id;
        flags_t control_bits;
    };

    struct
    {
        uint8_t msg_type;
        char* string;
    };
} Params_t;

typedef struct
{
    id_t id;
    Params_t params;
    //time_t time;
} Command_t;

#endif/* COMMAND_H */
