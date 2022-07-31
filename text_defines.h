#ifndef TXT_DEF_H
#define TXT_DEF_H

#include "_macro.h"
#include "gfx_video_defines.h"

#define CHAR_WIDTH  8
#define CHAR_HEIGHT 8

#define TAB_SIZE    4
#define TAB_SHIFT   LOWEST_SET_BIT(TAB_SIZE)
#define TAB_MASK    (TAB_SIZE-1)

#define MAX_SCREEN_COLS (SCREEN_WIDTH/CHAR_WIDTH)
#define MAX_SCREEN_ROWS (SCREEN_HEIGHT/CHAR_HEIGHT)

#define CURSOR_SYMBOL 219

#endif/* TXT_DEF_H */
