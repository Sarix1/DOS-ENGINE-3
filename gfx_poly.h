#ifndef POLY_H
#define POLY_H

#include "_common.h"
#include "gfx_draw_structs.h"

enum POLY
{
    POLY_SHIP,
    POLY_ASTEROID
};

Poly_t* getPoly(id_t id);

#endif/* POLY_H */
