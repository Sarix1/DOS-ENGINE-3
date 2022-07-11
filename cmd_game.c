#include "common.h"
#include "command.h"
#include "game.h"
#include "maths2.h"

void cmdSpawn(Event_t cmd) // this should go to game.c and only be declared, not defined here
{
    // id_t object_type = cmd.params.type;

    // for now we lack different types and a generic spawn function
    // instead, just spawn a ship

    spawnShip(vec2i(cmd.event.params.pos.x, cmd.event.params.pos.y), 0);
}