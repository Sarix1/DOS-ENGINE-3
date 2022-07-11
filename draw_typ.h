#ifndef DRAW_DEFS_H
#define DRAW_DEFS_H

#include "types.h"
#include "math_typ.h"

typedef struct
{
    Vec2 points[16];
    uint8_t num_points;
} Poly_t;

typedef struct
{
    byte* pixels;
    int16_t w, h;
    int16_t size;
    int16_t num_frames;
} Sprite_t;

typedef struct
{
    Sprite_t* sprite;
    byte* pixels;
    int16_t frame;
    int16_t frame_interval;
    fix16_16 scale_x;
    fix16_16 scale_y;
} Visible_t;

#endif/* DRAW_DEFS_H */
