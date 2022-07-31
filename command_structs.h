#ifndef CMD_TYP_H
#define CMD_TYP_H

#include "_common.h"

typedef union
{
    Vec2 v2;
    struct { int16_t a, b, c, d; } vars;
    struct { id_t id; int16_t mode; } state;
    struct { int16_t x, y, z; union {int16_t w; id_t id; id_t type; brad angle;} var; } pos;
    struct { id_t id; int str_offset; } cmd;
} Params_t;

typedef union
{
    Vec3 v3;
    struct { Vec2 v, u; } vecs;
    struct { Params_t a, b; } params;
} BigParams_t;

typedef union
{
    struct { id_t id; time_t tick; Params_t params; } data;
    BigParams_t big_params;
} Command_t;

typedef void (*fnp_cmd)(Command_t cmd);

#endif/* CMD_TYP_H */
