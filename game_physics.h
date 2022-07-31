#ifndef PHYSICS_H
#define PHYSICS_H

#define PHYS_MAX_SPEED  (FIXP_ONE*2)
#define PHYS_ACCELERATE (FIXP_ONE/4)
#define PHYS_DECELERATE (FIXP_ONE-(FIXP_ONE/20))
#define PHYS_TURN_RATE  BRAD_1_32ND_PI

void physics();

#endif/* PHYSICS_H */
