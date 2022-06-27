#ifndef VID_TYP_H
#define VID_TYP_H

#include "common.h"
#include "pal_typ.h"

typedef struct
{
    Palette_t   palette;
    byte*       screen;
    byte far*   offScreen;
    byte far*   drawSurface;
    int         offset_x;
    int         offset_y;
    time_t      frame;
    bool        init;
} Video_t;

#endif/* VID_TYP_H */
