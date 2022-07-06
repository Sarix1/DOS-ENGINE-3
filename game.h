#ifndef GAME_H
#define GAME_H

#include "game_def.h"
#include "game_typ.h"

#define PLAYER_OBJ g_Game.ObjectsById[g_Game.player_id]

extern GameData_t g_Game;

id_t createObject(int16_t x, int16_t y, brad angle, brad angvel,
                  fixp radius, fixp scale, Poly_t* poly, byte color);
void deleteObject(id_t id);
void deleteLastObject();
id_t spawnShip(int16_t x, int16_t y, brad angle);

#endif/* GAME_H */
