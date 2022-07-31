#include "_common.h"
#include "gfx_draw.h"
#include "gfx_draw_text.h"
#include "math_fixp.h"
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


void drawHitBoxAABB(Object_t* obj, byte color)
{
    Vec2 pos;
    pos.x = toInt(obj->pos.x);
    pos.y = toInt(a(obj->pos.y));
    drawRectFrameCenter(pos.x, pos.y, toInt(obj->radius<<1), a(toInt(obj->radius<<1)), color);
}

void drawHitBoxOBB(Object_t* obj, byte color)
{
    drawRectFrameRotated_v(vec2_F2I(obj->pos), toInt(obj->obb_h), toInt(obj->obb_w), obj->dir, color);
}

void drawObject(Object_t* obj)
{
    Vec2 pos;
    pos.x = toInt(obj->pos.x);
    pos.y = toInt(a(obj->pos.y));

    if (obj->angle != obj->last_angle)
    {
        vecs2scaleRotV(obj->transformed_poly.points, obj->poly->points, obj->poly->num_points, obj->scale, obj->dir);
        obj->last_angle = obj->angle;
    }

    #if DEBUG_HITBOX == 1
    //drawCircleFrame(pos.x, pos.y, toInt(obj->radius)<<1, COLOR_DEBUG_LINE);
    drawHitBoxOBB(obj, obj->color2);
    drawHitBoxAABB(obj, obj->color2);
    #endif

    #if ASPECT == 1
    drawShapeAspect(pos, obj->transformed_poly.points, obj->transformed_poly.num_points, obj->color);
    #else
    drawShape(pos, obj->transformed_poly.points, obj->transformed_poly.num_points, obj->color);
    #endif
}

void drawAllObjects()
{
    int i;
    for (i = 0; i < g_Game.object_count; i++)
        drawObject(&g_Game.Objects[i]);
    drawLineFixp(av2(PLAYER_OBJ->pos),
                 av2(vec2add(
                    PLAYER_OBJ->pos,
                    vec2scale(PLAYER_OBJ->dir,F(1000)))),
                 COLOR_GREEN);
}

void gameDraw()
{
    drawAllObjects();
}