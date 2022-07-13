#ifndef INP_TYP_H
#define INP_TYP_H

#include "inp_def.h"
#include "txt_typ.h"

typedef struct
{
    byte keycode;
    byte type;
    time_t time;
} InputEvent_t;

typedef struct
{
    byte up;
    byte down;
    byte left;
    byte right;
    byte UI_yes;
    byte UI_no;
    // should be an array where index = id of action, key = keycode
} KeyMap_t;

typedef struct
{
    flags_t       flags;

    KeyMap_t*     keymap;
    InputEvent_t  queue[KB_QUEUE_LENGTH];
    byte          keystates[KB_ARRAY_SIZE]; // TO-DO: split into multiple arrays
    byte          queue_head;
    byte          queue_tail;

    TextInput_t* input_field;
    fnp_input     input_callback;
} Input_t;

#endif/* INP_TYP_H */
