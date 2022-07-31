#ifndef INP_TYP_H
#define INP_TYP_H

#include "input_defines.h"
#include "text_structs.h"

typedef struct
{
    action_id_t bindings[256];
} KeyMap_t;

typedef struct
{
    time_t tick;
    byte type;
    union u_data
    {
        byte keycode;
        _Packed struct t_hid
        {
        int16_t x:10,
                y:10;
           byte button0:1,
                button1:1,
                button2:1,
                button3:1;
        } hid;
    } data;
} InputEvent_t; // these can be larger, there won't be so many of them
// there is no no point optimizing since they're not stored nor sent over net

typedef struct
{
    flags_t       flags;

    KeyMap_t*     keymap;
    InputEvent_t  EventQueue[KB_QUEUE_LENGTH];
    byte          KeyStates[KB_ARRAY_SIZE]; // TO-DO: split into multiple arrays
    byte          queue_head;
    byte          queue_tail;

    TextInput_t*  input_field;
    fnp_input     input_callback;
} Input_t;

#endif/* INP_TYP_H */
