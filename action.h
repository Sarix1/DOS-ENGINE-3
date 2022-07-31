#ifndef ACTION_H

#include "action_defines.h"
#include "action_structs.h"

extern controldata_t local_controldata;
//extern ActionQueue_t LocalActionQueue;

int generateAction(action_id_t action_id, byte state, time_t tick);
void processActions();

#endif/* ACTION_H */
