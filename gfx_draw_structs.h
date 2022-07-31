#ifndef DRAW_DEFS_H
#define DRAW_DEFS_H

#include "_types.h"
#include "math_fixp_structs.h"

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
} Texture_t;

typedef struct
{
    Texture_t* texture;
    byte* pixels;
    int16_t frame;
    int16_t frame_interval;
    fixp scale_x;
    fixp scale_y;
} Sprite_t;

#endif/* DRAW_DEFS_H */
