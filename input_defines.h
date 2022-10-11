#ifndef INP_DEF_H
#define INP_DEF_H

#include "_bits.h"
#include "input_keys.h"

#define KEYHANDLER_INT      9
#define SCAN_BUFFER_SIZE    32
#define KB_ARRAY_SIZE       256
#define KB_QUEUE_LENGTH     256

#define EV_INP_TYPE_KEYB    (BIT_0|BIT_1|BIT_2)
#define EV_INP_TYPE_MOUSE   BIT_3
#define EV_INP_TYPE_JOY     BIT_4
#define EV_INP_TYPE_HID     BIT_5
#define EV_INP_KEY_HIT      BIT_0
#define EV_INP_KEY_REL      BIT_1
#define KEY_IS_DOWN         BIT_2
  
#define SCAN_EXTENDED         0xE0
#define SCAN_EXT_PRTSC_START  SCAN_EXTENDED
#define SCAN_EXT_PRTSC_END    0x37
#define SCAN_EXT_PAUSE_START  0xE1
#define SCAN_EXT_PAUSE_END    0xC5
#define SCAN_SEQ_INDEX_PRTSC  0
#define SCAN_SEQ_INDEX_PAUSE  4

#define KEYCODE_EXTENDED    0x80
#define KEYCODE_RELEASED    0x80
 
#define INP_FLAG_CAPS_LOCK          BIT_0
#define INP_FLAG_REPEAT_KEYS        BIT_1
#define INP_FLAG_GLOBAL_KEYS        BIT_2
#define INP_FLAG_UI_CONTROL_KEYS    BIT_3
#define INP_FLAG_WRITE_TEXT         BIT_4
#define INP_FLAG_GAME_CONTROL       BIT_5

#endif/* INP_DEF_H */
