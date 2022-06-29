#ifndef INP_TYP_H
#define INP_TYP_H

#include "inp_def.h"
#include "txt_inp.h"

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
    KeyEvent_t queue[KB_QUEUE_LENGTH];
    byte keystates[KB_ARRAY_SIZE]; // TO-DO: split into multiple arrays
    KeyMap_t* keymap;
    TextField_t* text_field;
    byte queue_head;
    byte queue_tail;
    bool caps_lock   : 1;
    bool repeat_keys : 1;
    bool text_input  : 1;
    bool text_enter  : 1;
    bool init        : 1;
} Input_t;

#endif/* INP_TYP_H */
