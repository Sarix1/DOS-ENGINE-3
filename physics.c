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

void physics()
{
    PLAYER_OBJ->control = player_control; // ^ should be in a "logic" loop that  comes before physics, and includes AI, game logic, etc.
    controlObject(PLAYER_OBJ);
    moveAllObjects();
}