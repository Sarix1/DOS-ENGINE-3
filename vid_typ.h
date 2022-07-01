#ifndef VID_TYP_H
#define VID_TYP_H

#include "common.h"
#include "pal_typ.h"

typedef struct
{
    Palette_t   palette;
    byte*       screen;
    byte far*   off_screen;
    byte far*   surface;
    int         offset_x;
    int         offset_y;
    time_t      frame;
} Video_t;

#endif/* VID_TYP_H */
