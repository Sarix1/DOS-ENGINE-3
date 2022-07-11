#ifndef STATE_H
#define STATE_H

#include "stat_def.h"
#include "stat_typ.h"

extern StateManager_t g_StateMgr;

int pushState(id_t new_);
int popState();
void updateStates();
void drawStates();
void setStateFlags(id_t state, flags_t flags);
void clearStateFlags(id_t state, flags_t flags);

#endif/* STATE_H */
