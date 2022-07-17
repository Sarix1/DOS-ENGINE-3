#include "common.h"
#include "physics.h"
#include "controls.h"
#include "maths.h"
#include "game.h"

extern control_t player_control;

void controlObject(Object_t* obj)
{
    switch (obj->control & (CONTROL_LEFT|CONTROL_RIGHT))
    {
        case CONTROL_LEFT:
            obj->angvel = PHYS_TURN_RATE;
            break;
        case CONTROL_RIGHT:
            obj->angvel = -PHYS_TURN_RATE;
            break;
        default:
            obj->angvel = 0;
    }

    switch (obj->control & (CONTROL_UP|CONTROL_DOWN))
    {
        case CONTROL_UP:
            obj->vel = vec2add(obj->vel, vec2scale(obj->dir, PHYS_ACCELERATE));
            break;
        case CONTROL_DOWN:
            obj->vel = vec2add(obj->vel, vec2scale(obj->dir, -PHYS_ACCELERATE));
            break;
        default:
            obj->vel.x = fixpMul(obj->vel.x, PHYS_DECELERATE);
            obj->vel.y = fixpMul(obj->vel.y, PHYS_DECELERATE);
    }
}

void moveObject(Object_t* obj)
{
    obj->pos.x += obj->vel.x;
    obj->pos.y += obj->vel.y;
    obj->angle += obj->angvel;
    obj->dir = newVec2_angle(obj->angle);

    if (obj->pos.x-obj->radius > F(SCREEN_WIDTH))
        obj->pos.x = -obj->radius;
    else if (obj->pos.x+obj->radius < 0)
       obj->pos.x = F(SCREEN_WIDTH)+obj->radius;

    if (obj->pos.y-obj->radius > F(A(SCREEN_HEIGHT)))
        obj->pos.y = -obj->radius;
    else if (obj->pos.y+obj->radius < 0)
       obj->pos.y = F(A(SCREEN_HEIGHT))+obj->radius;
}

void moveAllObjects()
{
    int i;
    for (i = 0; i < g_Game.object_count; i++)
        moveObject(&g_Game.Objects[i]);
}

void polyCircleIntersect(Vec2 circle, fixp radius, Poly_t* poly, int num_points)
{
    Vec2 a = poly->points[0];
    Vec2 b = poly->points[1];
}

int intersectAABB(Vec2 p0, int32_t w0_half, int32_t h0_half,
                 Vec2 p1, int32_t w1_half, int32_t h1_half)
{
    if  (p0.x+w0_half < p1.x-w1_half || p0.x-w0_half > p1.x+w1_half)
        return DONT_INTERSECT;
    if  (p0.y+h0_half < p1.y-h1_half || p0.y-h0_half > p1.y+h1_half)
        return DONT_INTERSECT;
    return DO_INTERSECT;
}

// p == center origins of bounding boxes
// dir == alignments of bounding boxes
// w == HALF widths of bounding boxes ("horizontal radius")
// h == HALF heights of bounding boxes ("vertical radius")
// move to maths.c
int intersectOBB(Vec2 p0, Vec2 dir0, fixp w0_half, fixp h0_half,
                 Vec2 p1, Vec2 dir1, fixp w1_half, fixp h1_half)
{
    Vec2 dist = vec2sub(p1,p0);
    Vec2 local_x0 = vec2_90left(dir0);
    Vec2 local_y0 = dir0;
    Vec2 local_x1 = vec2_90left(dir1);
    Vec2 local_y1 = dir1;

    fixp proj_len, proj_wh, x0x1, x0y1, y0x1, y0y1;

    x0x1 = abs(vec2fixpDot(local_x0, local_x1));
    x0y1 = abs(vec2fixpDot(local_x0, local_y1));

    // x0
    proj_wh = fixpMul(w1_half,x0x1) + fixpMul(h1_half,x0y1);
    proj_len = abs(vec2fixpDot(local_x0, dist));
    if (proj_len > w0_half + proj_wh)
        return DONT_INTERSECT;

    y0x1 = abs(vec2fixpDot(local_y0, local_x1));
    y0y1 = abs(vec2fixpDot(local_y0, local_y1));

    // y0
    proj_wh = fixpMul(w1_half,y0x1) + fixpMul(h1_half,y0y1);
    proj_len = abs(vec2fixpDot(local_y0, dist));
    if (proj_len > h0_half + proj_wh)
        return DONT_INTERSECT;

    // x1
    proj_wh = fixpMul(w0_half,x0x1) + fixpMul(h0_half,y0x1);
    proj_len = abs(vec2fixpDot(local_x1, dist));
    if (proj_len > w1_half + proj_wh)
        return DONT_INTERSECT;

    // y1
    proj_wh = fixpMul(w0_half,x0y1) + fixpMul(h0_half,y0y1);
    proj_len = abs(vec2fixpDot(local_y1, dist));
    if (proj_len > h1_half + proj_wh)
        return DONT_INTERSECT;

    return DO_INTERSECT;
}

int intersectAll()
{
    int i;
    int any_intersect = DONT_INTERSECT;

    for (i = 1; i < g_Game.object_count; i++)
    {
        int intersect = DONT_INTERSECT;

        if (intersectAABB(
            PLAYER_OBJ->pos,
            PLAYER_OBJ->radius,
            PLAYER_OBJ->radius,
            g_Game.Objects[i].pos,
            g_Game.Objects[i].radius,
            g_Game.Objects[i].radius)
            == DO_INTERSECT)
        {
            intersect = intersectOBB
            (
                PLAYER_OBJ->pos,
                PLAYER_OBJ->dir,
                PLAYER_OBJ->bbox_w,
                PLAYER_OBJ->bbox_h,
                g_Game.Objects[i].pos,
                g_Game.Objects[i].dir,
                g_Game.Objects[i].bbox_w,
                g_Game.Objects[i].bbox_h
            );
            any_intersect |= intersect;
        }

        if (intersect)      
            g_Game.Objects[i].color2 = COLOR_RED;
        else
            g_Game.Objects[i].color2 = COLOR_HITBOX;
    }
    if (any_intersect)
        PLAYER_OBJ->color2 = COLOR_RED;
    else
        PLAYER_OBJ->color2 = COLOR_HITBOX;

    return any_intersect;
}

void physics()
{
    int i = 0;
    PLAYER_OBJ->control = player_control; // ^ should be in a "logic" loop that  comes before physics, and includes AI, game logic, etc.
    controlObject(PLAYER_OBJ);
    moveAllObjects();
    intersectAll();
}