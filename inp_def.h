#ifndef INP_DEF_H
#define INP_DEF_H

#include "keys.h"
#include "controls.h"

#define KB_ARRAY_SIZE       256
#define KB_QUEUE_LENGTH     256
#define KEY_SPECIAL         0xE0
#define KEYSTATE_RELEASED   0x80
#define KEYSTATE_HIT        0x40
#define KEYSTATE_DOWN       0x01
#define KEYHANDLER_INT      9

#define INPUT_FLAG_CAPS     BIT_0
#define INPUT_FLAG_REPEAT   BIT_1
#define INPUT_FLAG_GLOBAL   BIT_2
#define INPUT_FLAG_UI       BIT_3
#define INPUT_FLAG_TEXT     BIT_4
#define INPUT_FLAG_GAME     BIT_5

#endif/* INP_DEF_H */
