#include "_common.h"
#include "command_structs.h"
#include "game.h"
#include "math_fixp_inline.h"

void cmdSpawn(Command_t cmd) // this should go to game.c and only be declared, not defined here
{
    // id_t object_type = cmd.params.type;

    // for now we lack different types and a generic spawn function
    // instead, just spawn a ship

    spawnShip(newVec2_I2F(cmd.event.params.pos.x, cmd.event.params.pos.y), 0);
}