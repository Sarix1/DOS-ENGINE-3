#ifndef INPUT_H
#define INPUT_H

#include "_common.h"
#include "input_structs.h"
#include "input_defines.h"

extern Input_t g_Input;

void handleInputEvents();
void initKeyMap();

inline byte isKeyDown(byte k)
{
    return g_Input.KeyStates[k] & KEY_IS_DOWN;
}

inline byte wasKeyHit(byte k)
{
    return g_Input.KeyStates[k] & EV_INP_KEY_HIT;
}

inline byte wasKeyReleased(byte k)
{
    return g_Input.KeyStates[k] & EV_INP_KEY_REL;
}

#endif/* INPUT_H */
