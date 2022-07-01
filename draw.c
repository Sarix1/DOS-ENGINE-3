#include "common.h"
#include "gfx.h"
#include "txt_draw.h"
#include "maths.h"
#include "timer.h"
#include "game.h"

/*
#define MAX_PARTICLES 256

typedef struct
{
    Vec2 pos;
    Vec2 vel;
    fixp color;
    fixp color_step;
    int life;
} Particle_t;

Particle_t particles[MAX_PARTICLES];
*/
/*
void drawStars()
{
    static Vec3 stars[256];

    int i,x,y;
}
*/

void drawObject(Object_t* obj)
{
    if (obj->angle != obj->last_angle)
    {
        vecs2scaleRotV(obj->points, obj->poly->points, obj->poly->num_points, obj->scale, obj->dir);
        obj->last_angle = obj->angle;
    }
    #if ASPECT == 1
    drawShapeScreen(vec2fixpToInt(obj->pos), obj->points, obj->num_points, obj->color);
    #else
    drawShape(vec2fixpToInt(obj->pos), obj->points, obj->num_points, obj->color);
    #endif
}

#if DEBUG == 1
void drawDebug()
{
    int i;
    int y = 0;

    for (i = 0; i < NUM_DEBUG; i++)
    {
        if (debug[i][0] != '\0')
            y += ((drawText(0, y, 0, 0, debug[i], AUTO, COLOR_DEBUG, TEXT_FX_NONE) + 1) << 3);
    }
}
#endif

void draw()
{
    drawFill(COLOR_BG);
    drawObject(PLAYER_OBJ);

    #if DEBUG == 1
    drawDebug();
    #endif
}