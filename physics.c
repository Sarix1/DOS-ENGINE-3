#include "physics.h"
#include "maths.h"
#include "controls.h"
#include "game.h"

extern control_t player_control;

#define PHYS_MAX_SPEED  (FIX_ONE*2)
#define PHYS_ACCELERATE (FIX_ONE/8)
#define PHYS_TURN_RATE  DEG_5

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
            obj->vel.x = fixpMul(obj->vel.x, (FIX_ONE-1000));
            obj->vel.y = fixpMul(obj->vel.y, (FIX_ONE-1000));
    }
}

void moveObject(Object_t* obj)
{
    obj->pos.x += obj->vel.x;
    obj->pos.y += obj->vel.y;
    obj->angle += obj->angvel;
    obj->dir = vec2unit(obj->angle);
}

void physics()
{
    PLAYER_OBJ->control = player_control;
    // ^ should be in a "logic" loop that  comes before physics, and includes AI, game logic, etc.
    controlObject(PLAYER_OBJ);
    moveObject(PLAYER_OBJ);
}