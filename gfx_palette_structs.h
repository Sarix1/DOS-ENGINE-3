#ifndef PALETTE_STRUCTS_H
#define PALETTE_STRUCTS_H

#include "_common.h"

typedef struct
{
    byte r,g,b;
} Color_t;

typedef struct
{
    Color_t colors[256];
} Palette_t;

#endif/* PALETTE_STRUCTS_H */
