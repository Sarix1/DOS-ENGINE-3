#ifndef STAT_TYP_H
#define STAT_TYP_H

#include "common.h"
#include "stat_def.h"

typedef struct
{
    id_t    id;     // who am I?
    flags_t flags;  // enable update/draw/input etc.
    i_fnp   init;   // state pushed on stack; returns SUCCESS/ERROR
    i_fnp   quit;   // state popped off stack; returns SUCCESS/ERROR
    fnp     enter;  // becomes top of state; re-enable input, etc.
    fnp     leave;  // un-becomes top of state; disable some stuff
    fnp     update; // update the state logic
    fnp     draw;   // draw the state
} State_t;

typedef struct
{
    flags_t  flags;
    int      state_count;
    State_t* Stack[NUM_STATES];
} StateManager_t;

#endif/* STAT_TYP_H */
