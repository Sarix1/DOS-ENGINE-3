#include <string.h>
#include "_common.h"
#include "_malloc.h"
#include "_debug.h"

#include "game.h"
#include "game_physics.h"

#include "timer.h"
#include "input.h"
#include "action.h"

#include "math_fixp_inline.h"
#include "gfx_draw_defines.h"
#include "gfx_poly.h"

GameData_t g_Game = {0};

int gameInit()
{
    g_Game.object_capacity = OBJ_CHUNK;
    g_Game.id_capacity = OBJ_CHUNK;
    g_Game.Objects = (Object_t*)malloc(g_Game.object_capacity * sizeof(Object_t));
    g_Game.ObjectsById = (Object_t**)calloc(g_Game.id_capacity, sizeof(void*));

    g_Game.player_id = spawnShip(newVec2_I2F(SCREEN_WIDTH/2, A(SCREEN_HEIGHT/2)), DEG_90);

    // objects should use template structs
    // createObject accepts position, velocity, angle, etc. but nothing further
    // it will copy values from the template, and override some of them with given parameters
    // OBJTYPE_ enum will index the template
    // if a pointer to an object struct is given as parameter, that will be used instead
    // otherwise NULL should be given
    // this enables copying of objects, that should have its own wrapper function to erode user parameters
    // it should accept an angle or direction; if direction is {0,0} angle will be used
    createObject(newVec2_I2F(50, 50),  newVec2(-FIXP_025,-FIXP_005), newVec2_angle(0),  DEG_5, F(22), F(15), F(15), FIXP_1, getPoly(1), COLOR_ASTEROID);
    createObject(newVec2_I2F(300,150), newVec2( FIXP_078,-FIXP_056), newVec2_angle(0), -DEG_3, F(22), F(15), F(15), FIXP_1, getPoly(1), COLOR_ASTEROID);
    createObject(newVec2_I2F(100,180), newVec2(-FIXP_050, FIXP_1_4), newVec2_angle(0),  DEG_9, F(22), F(15), F(15), FIXP_1, getPoly(1), COLOR_ASTEROID);
    createObject(newVec2_I2F(200,80),  newVec2( FIXP_015, FIXP_1_5), newVec2_angle(0), -DEG_2, F(22), F(15), F(15), FIXP_1, getPoly(1), COLOR_ASTEROID);

    //g_Game.Objects[1].vel.x = F(-1);
    //g_Game.Objects[2].vel.x = F(1);
    //g_Game.Objects[3].vel.x = F(2);

    return SUCCESS;
}

int gameQuit()
{
    g_Game.object_capacity = 0;
    g_Game.id_capacity = 0;
    free(g_Game.Objects);
    free(g_Game.ObjectsById);

    return SUCCESS;
}

void gameEnter()
{
    g_Input.flags |= INP_FLAG_GAME_CONTROL;
    g_Timer.enable_ticks = 1;
}

void gameLeave()
{
    g_Input.flags &= ~INP_FLAG_GAME_CONTROL;
}

void gameUpdate()
{
    processActions();
    physics();
    #if DEBUG_INFO == 1
    sprintf(debug[DEBUG_OBJECTS], "Objects: %d\n", g_Game.object_count);
    #endif
}

void gameEsc()
{
    ;
}

static id_t getNewId()
{
    id_t id; // skip 0
    for (id = 1; id < g_Game.id_capacity; id++)
        if (g_Game.ObjectsById[id] == NULL)
            return id;

    g_Game.id_capacity += OBJ_CHUNK;
    g_Game.ObjectsById = (Object_t**)realloc(g_Game.ObjectsById, g_Game.id_capacity * sizeof(void*));
    memset(g_Game.ObjectsById, 0, OBJ_CHUNK * sizeof(void*)); // set new pointers to NULL

    return id;
}

id_t createObject(Vec2 pos, Vec2 vel, Vec2 dir, brad angvel,
                  fixp radius, fixp obb_w, fixp obb_h,
                  fixp scale, Poly_t* poly,  byte color)
{
    Object_t* obj;
    id_t id = getNewId();

    if (g_Game.object_count >= g_Game.object_capacity)
    {
        g_Game.object_capacity += OBJ_CHUNK;
        g_Game.Objects = (Object_t*)realloc(g_Game.Objects, g_Game.object_capacity * sizeof(Object_t));
        // to do: ensure successful allocation
    }

    obj = g_Game.ObjectsById[id] = &g_Game.Objects[g_Game.object_count++];
    obj->pos = pos;
    obj->vel = vel;
    obj->dir = dir;
    obj->angle = vec2angle(dir);
    obj->angvel = angvel;
    obj->radius = radius;
    obj->obb_w = obb_w;
    obj->obb_h = obb_h;
    obj->poly = poly;
    memcpy(obj->transformed_poly.points, poly->points, poly->num_points*sizeof(Vec2));
    obj->transformed_poly.num_points = obj->poly->num_points;
    obj->scale = scale;
    obj->color = color;
    obj->color2 = COLOR_HITBOX;

    return id;
}

void deleteObject(id_t id)
{
    if (g_Game.ObjectsById[id] != &g_Game.Objects[g_Game.object_count])
        *g_Game.ObjectsById[id] = g_Game.Objects[g_Game.object_count-1];

    g_Game.object_count--;
    g_Game.ObjectsById[id] = NULL;

    if (g_Game.object_count < g_Game.object_capacity - OBJ_CHUNK)
    {
        g_Game.object_capacity -= OBJ_CHUNK;
        g_Game.Objects = (Object_t*)realloc(g_Game.Objects, g_Game.object_capacity * sizeof(Object_t));
    }
}

void deleteLastObject()
{
    if (g_Game.object_count > 0)
        deleteObject(g_Game.object_count-1);
}

id_t spawnShip(Vec2 pos, brad angle)
{
    return createObject(pos, newVec2_I2F(0,0), newVec2_angle(0), 0, F(32), F(8), F(30), F(1), getPoly(POLY_SHIP), COLOR_SHIP);
}