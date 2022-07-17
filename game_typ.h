#ifndef GAME_TYP_H
#define GAME_TYP_H

#include "common.h"
#include "math_def.h"
#include "draw_typ.h"

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
    fixp bbox_w;
    fixp bbox_h;
    control_t control;
    //gfx
    Poly_t* poly;
    Poly_t tPoly;
    fixp scale;
    byte color;
    byte color2;
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

#endif/* GAME_TYP_H */
