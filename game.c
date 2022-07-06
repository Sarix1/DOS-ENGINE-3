#include "common.h"
#include "game.h"
#include "malloc_.h"
#include "maths2.h"
#include "gfx_def.h"
#include <string.h>

GameData_t g_Game = {0};

void physics();
void draw();

int initGame()
{
    g_Game.object_capacity = OBJ_CHUNK;
    g_Game.id_capacity = OBJ_CHUNK;
    g_Game.Objects = malloc(g_Game.object_capacity * sizeof(Object_t));
    g_Game.ObjectsById = calloc(g_Game.id_capacity, sizeof(void*));

    g_Game.player_id = spawnShip(160, A(100), DEG_90);

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

void updateGame()
{
    physics();
}

void drawGame()
{
    draw();
}

static id_t getNewId()
{
    id_t id; // skip 0
    for (id = 1; id < g_Game.id_capacity; id++)
        if (g_Game.ObjectsById[id] == NULL)
            return id;

    g_Game.id_capacity += OBJ_CHUNK;
    g_Game.ObjectsById = realloc(g_Game.ObjectsById, g_Game.id_capacity * sizeof(void*));
    memset(g_Game.ObjectsById, 0, OBJ_CHUNK * sizeof(void*)); // set new pointers to NULL

    return id;
}

id_t createObject(int16_t x, int16_t y, brad angle, brad angvel,
                  fixp radius, fixp scale, Poly_t* poly,  byte color)
{
    Object_t* obj;
    id_t id = getNewId();

    if (g_Game.object_count >= g_Game.object_capacity)
    {
        g_Game.object_capacity += OBJ_CHUNK;
        g_Game.Objects = realloc(g_Game.Objects, g_Game.object_capacity * sizeof(Object_t));
        // to do: ensure successful allocation
    }

    obj = g_Game.ObjectsById[id] = &g_Game.Objects[g_Game.object_count];
    obj->pos.x = toFixp(x);
    obj->pos.y = toFixp(y);
    obj->vel.x = 0;
    obj->vel.y = 0;
    obj->dir = vec2unit(angle);
    obj->angle = angle;
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
        g_Game.Objects = realloc(g_Game.Objects, g_Game.object_capacity * sizeof(Object_t));
    }
}

void deleteLastObject()
{
    if (g_Game.object_count > 0)
        deleteObject(g_Game.object_count-1);
}

id_t spawnShip(int16_t x, int16_t y, brad angle)
{
    static Poly_t Poly = { {{10,0}, {-10,-8}, {-5,0}, {-10,8}}, 4 };

    return createObject(x, y, angle, 0, F(10), F(1), &Poly, COLOR_SHIP);
}