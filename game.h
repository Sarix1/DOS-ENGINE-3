#ifndef GAME_H
#define GAME_H

#include "game_def.h"
#include "game_typ.h"

#define PLAYER_OBJ g_Game.ObjectsById[g_Game.player_id]

extern GameData_t g_Game;

id_t createObject(Vec2 pos, Vec2 vel, Vec2 dir, brad angvel,
                  fixp radius, fixp scale, Poly_t* poly, byte color);
void deleteObject(id_t id);
void deleteLastObject();
id_t spawnShip(Vec2 pos, brad angle);

#endif/* GAME_H */
