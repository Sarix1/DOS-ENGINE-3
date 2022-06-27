#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "common.h"
#include "mat_def.h"
#include "gfx_typ.h"

typedef struct
{
    //physics
    Vec2 pos;
    Vec2 vel;
    Vec2 dir;
    brad angle;
    brad last_angle;
    brad angvel;
    fixp radius;
    control_t control;
    //gfx
    Poly_t* poly;
    Vec2 points[16];
    int num_points;
    fixp scale;
    byte color;
} Object_t;

typedef struct
{
    //Map_t Map;
    Object_t* Objects;
    Object_t** ObjectsById;
    id_t object_count;
    id_t object_capacity;
    id_t max_id;
    id_t id_capacity;
    id_t player_id;
} GameData_t;

#endif/* GAME_STRUCTS_H */
