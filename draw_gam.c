#include "common.h"
#include "draw.h"
#include "draw_txt.h"
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
    Vec2 pos;
    pos.x = toInt(obj->pos.x);
    pos.y = toInt(a(obj->pos.y));

    #if DEBUG_HITBOX == 1
    drawCircleFrame(pos.x, pos.y, toInt(obj->radius)<<1, COLOR_DEBUG_LINE);
    #endif

    if (obj->angle != obj->last_angle)
    {
        vecs2scaleRotV(obj->tPoly.points, obj->poly->points, obj->poly->num_points, obj->scale, obj->dir);
        obj->last_angle = obj->angle;
    }

    #if ASPECT == 1
    drawShapeAspect(pos, obj->tPoly.points, obj->tPoly.num_points, obj->color);
    #else
    drawShape(pos, obj->tPoly.points, obj->tPoly.num_points, obj->color);
    #endif
}

void drawAllObjects()
{
    int i;
    for (i = 0; i < g_Game.object_count; i++)
        drawObject(&g_Game.Objects[i]);
}

void drawGame()
{
    drawFill(COLOR_BG);
    drawAllObjects();
}