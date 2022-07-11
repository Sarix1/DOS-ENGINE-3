#include <string.h>
#include "common.h"
#include "game.h"
#include "malloc_.h"
#include "maths2.h"
#include "physics.h"
#include "draw_def.h"
#include "input.h"
#include "poly.h"
#include "debug.h"

GameData_t g_Game = {0};

int initGame()
{
    g_Game.object_capacity = OBJ_CHUNK;
    g_Game.id_capacity = OBJ_CHUNK;
    g_Game.Objects = (Object_t*)malloc(g_Game.object_capacity * sizeof(Object_t));
    g_Game.ObjectsById = (Object_t**)calloc(g_Game.id_capacity, sizeof(void*));

    g_Game.player_id = spawnShip(vec2i(SCREEN_WIDTH/2, A(SCREEN_HEIGHT/2)), DEG_90);

    createObject(vec2i(50, 50),  vec2i(1,2),   vec2unit(0), DEG_5, F(15), F(1), getPoly(1), COLOR_ASTEROID);
    createObject(vec2i(300,150), vec2i(2,-1),  vec2unit(0), -DEG_3, F(15), F(1), getPoly(1), COLOR_ASTEROID);
    createObject(vec2i(100,180), vec2i(-1,-2), vec2unit(0), DEG_9, F(15), F(1), getPoly(1), COLOR_ASTEROID);
    createObject(vec2i(200,80),  vec2i(2,-1),  vec2unit(0), -DEG_2, F(15), F(1), getPoly(1), COLOR_ASTEROID);

    return SUCCESS;
}

int quitGame()
{
    g_Game.object_capacity = 0;
    g_Game.id_capacity = 0;
    free(g_Game.Objects);
    free(g_Game.ObjectsById);

    return SUCCESS;
}

void enterGame()
{
    g_Input.flags |= INPUT_FLAG_GAME;
}

void leaveGame()
{
    g_Input.flags &= ~INPUT_FLAG_GAME;
}

void updateGame()
{
    physics();
    #if DEBUG_INFO == 1
    sprintf(debug[DEBUG_OBJECTS], "Objects: %d\n", g_Game.object_count);
    #endif
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
                  fixp radius, fixp scale, Poly_t* poly,  byte color)
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
    obj->poly = poly;
    memcpy(obj->points, poly->points, poly->num_points*sizeof(Vec2));
    obj->num_points = obj->poly->num_points;
    obj->scale = scale;
    obj->color = color;

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
    return createObject(pos, vec2i(0,0), vec2unit(0), 0, F(10), F(1), getPoly(POLY_SHIP), COLOR_SHIP);
}