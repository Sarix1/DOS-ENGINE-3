#include "gfx_poly.h"
#include "gfx_draw_structs.h"

static Poly_t poly_box = {
{
    {-10,-10},
    {10,-10},
    {10,10},
    {-10,10}
},
4 };

static Poly_t poly_ship = {
{
    {12,0},
    {-8,-8},
    {-3,0},
    {-8,8}
},
4 };

static Poly_t poly_asteroid = {
{
    {-15, -5},
    {-5, -15},
    {5,  -15},
    {15,  -5},
    {15,   5},
    {5,   15},
    {-5,  15},
    {-15,  5},
},
8 };

Poly_t* getPoly(id_t id)
{
    switch (id)
    {
    case POLY_SHIP:
        return &poly_ship;
    case POLY_ASTEROID:
        return &poly_asteroid;
    }
    return &poly_box;
}