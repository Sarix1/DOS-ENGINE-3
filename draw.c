#include "gfx.h"
#include "game.h"
#include "maths.h"
#include "colors.h"

void drawObject(Object_t* obj)
{
    if (obj->angle != obj->last_angle)
    {
        vecs2scaleRotV(obj->points, obj->poly->points, obj->poly->num_points, obj->scale, obj->dir);
        obj->last_angle = obj->angle;
    }
    drawShape(vec2fixpToInt(obj->pos), obj->points, obj->num_points, obj->color);
}

void draw()
{
    drawFill(BLACK);
    drawObject(PLAYER_OBJ);
}