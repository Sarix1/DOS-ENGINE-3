#ifndef STATE_H
#define STATE_H

#include "state_defines.h"
#include "state_structs.h"

extern StateManager_t g_StateMgr;

State_t* getState(id_t id);
State_t* getTopState();
void pushState(id_t new_);
void popState();
void removeState(id_t id);
void updateStates();
void drawStates();
void setStateFlags(id_t state, flags_t flags);
void clearStateFlags(id_t state, flags_t flags);
flags_t getStateFlags(id_t state);
State_t* getTopState();

#endif/* STATE_H */
