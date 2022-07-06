#ifndef STATE_H
#define STATE_H

#include "stat_def.h"
#include "stat_typ.h"

extern StateManager_t g_StateMgr;

int pushState(id_t new_);
int popState();
void updateStates();
void drawStates();

#endif/* STATE_H */
