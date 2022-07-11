#ifndef POLY_H
#define POLY_H

#include "common.h"
#include "draw_typ.h"

enum POLY
{
    POLY_SHIP,
    POLY_ASTEROID
};

Poly_t* getPoly(id_t id);

#endif/* POLY_H */
