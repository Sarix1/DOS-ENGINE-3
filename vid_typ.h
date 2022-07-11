#ifndef VID_TYP_H
#define VID_TYP_H

#include "common.h"
#include "pal_typ.h"

typedef struct
{
    byte*       screen;
    byte far*   off_screen;
    byte far*   surface;
    Palette_t*  palette;
    int         offset_x;
    int         offset_y;
    byte        bg_color;
    byte        text_color;
} Video_t;

#endif/* VID_TYP_H */
