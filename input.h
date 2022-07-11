#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "inp_typ.h"
#include "inp_def.h"

extern Input_t g_Input;

int handleGlobalKeys(InputEvent_t event);

inline byte isKeyDown(byte k)
{
    return g_Input.keystates[k] & KEYSTATE_DOWN;
}

inline byte wasKeyHit(byte k)
{
    return g_Input.keystates[k] & KEYSTATE_HIT;
}

inline byte wasKeyReleased(byte k)
{
    return g_Input.keystates[k] & KEYSTATE_RELEASED;
}

#endif/* INPUT_H */
