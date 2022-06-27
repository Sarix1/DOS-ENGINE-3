#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "keys.h"
#include "txt_inp.h"

//defines
#define KB_ARRAY_SIZE       256
#define KB_QUEUE_LENGTH     256
#define KEY_SPECIAL         0xE0
#define KEYSTATE_RELEASED   0x80
#define KEYSTATE_HIT        0x40
#define KEYSTATE_DOWN       0x01
#define KEYHANDLER_INT      9

//structs
typedef struct
{
    byte keycode;
    byte type;
    time_t time;
} KeyEvent_t;

typedef struct
{
    byte up;
    byte down;
    byte left;
    byte right;
    // should be an array where index = id of action, key = keycode
} KeyMap_t;

typedef struct
{
    KeyMap_t* keymap;
    KeyEvent_t queue[KB_QUEUE_LENGTH];
    byte keystates[KB_ARRAY_SIZE];
    byte keystrokes[KB_ARRAY_SIZE];
    byte keyreleases[KB_ARRAY_SIZE];
    byte queue_head;
    byte queue_tail;
    bool caps_lock   : 1;
    bool repeat_keys : 1;
    bool text_input  : 1;
    bool text_enter  : 1;
    TextField_t* text_field;
    //control_t player_control;
} Input_t; // possibly move all variables as static into input.c global scope

//externs
extern Input_t g_Input;

//functions
int initInput();
int quitInput();
void handleInputEvents();

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
