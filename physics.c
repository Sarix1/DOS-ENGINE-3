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
    obj->dir = vec2unit(obj->angle);

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

// p == center origins of bounding boxes
// dir == alignments of bounding boxes
// w == HALF widths of bounding boxes ("horizontal radius")
// h == HALF heights of bounding boxes ("vertical radius")
int intersectOBB(Vec2 p0, Vec2 dir0, fixp w0, fixp h0,
                 Vec2 p1, Vec2 dir1, fixp w1, fixp h1)
{
    Vec2 dist = vec2sub(p1,p0);
    Vec2 axis, axis_x, axis_y, vw, vh;
    fixp proj_dist, proj_mag, proj_w, proj_h;

    axis_x = vec2turnLeft(dir0);
    axis_y = dir0;
    vw = vec2scale(axis_x,w0);
    vh = vec2scale(axis_y,h0);

    proj_dist = vec2dot(axis_x,dist);
    proj_mag = sqrtF2F(proj_dist);
    proj_w = vec2dot(axis_x,vw);
    proj_h = vec2dot(axis_x,vh);
    if (proj_dist > w0*proj_mag + proj_w + proj_h)
        return DONT_INTERSECT;

    proj_dist = vec2dot(axis_y,dist);
    proj_mag = sqrtF2F(proj_dist);
    proj_w = vec2dot(axis_y,vw);
    proj_h = vec2dot(axis_y,vh);
    if (proj_dist > h0*proj_mag + proj_w + proj_h)
        return DONT_INTERSECT;

    axis_x = vec2turnLeft(dir1);
    axis_y = dir1;
    vw = vec2scale(axis_x,w1);
    vh = vec2scale(axis_y,h1);

    proj_dist = vec2dot(axis_x,dist);
    proj_mag = sqrtF2F(proj_dist);
    proj_w = vec2dot(axis_x,vw);
    proj_h = vec2dot(axis_x,vh);
    if (proj_dist > w1*proj_mag + proj_w + proj_h)
        return DONT_INTERSECT;

    proj_dist = vec2dot(axis_y,dist);
    proj_mag = sqrtF2F(proj_dist);
    proj_w = vec2dot(axis_y,vw);
    proj_h = vec2dot(axis_y,vh);
    if (proj_dist > h1*proj_mag + proj_w + proj_h)
        return DONT_INTERSECT;

    return DO_INTERSECT;
}

void physics()
{
    int i;
    PLAYER_OBJ->control = player_control; // ^ should be in a "logic" loop that  comes before physics, and includes AI, game logic, etc.
    controlObject(PLAYER_OBJ);
    moveAllObjects();

    i = intersectOBB
    (
        PLAYER_OBJ->pos,           PLAYER_OBJ->dir,
        PLAYER_OBJ->radius,        PLAYER_OBJ->radius,
        g_Game.Objects[1].pos,     g_Game.Objects[1].dir,
        g_Game.Objects[1].radius,  g_Game.Objects[1].radius
    );

    if (i == DO_INTERSECT)
        PLAYER_OBJ->color = COLOR_RED;
    else
        PLAYER_OBJ->color = COLOR_BLUE;
}