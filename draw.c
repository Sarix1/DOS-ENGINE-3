#include "common.h"
#include "gfx.h"
#include "txt_draw.h"
#include "maths.h"
#include "game.h"

void drawObject(Object_t* obj)
{
    if (obj->angle != obj->last_angle)
    {
        vecs2scaleRotV(obj->points, obj->poly->points, obj->poly->num_points, obj->scale, obj->dir);
        obj->last_angle = obj->angle;
    }
    drawShapeScreen(vec2fixpToInt(obj->pos), obj->points, obj->num_points, obj->color);
}

#if DEBUG == 1
void drawDebug()
{
    int i;
    int y = 0;

    for (i = 0; i < NUM_DEBUG; i++)
    {
        if (debug[i][0] != '\0')
            y += ((drawText(0, y, 0, 0, debug[i], WHITE, TEXT_FX_NONE) + 1) << 3);
    }
}
#endif

void draw()
{
    drawFill(BLUE);
    drawObject(PLAYER_OBJ);

    #if DEBUG == 1
    drawDebug();
    #endif
}