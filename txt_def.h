#ifndef TXT_DEF_H
#define TXT_DEF_H

#include "macro.h"
#include "vid_def.h"

#define CHAR_WIDTH  8
#define CHAR_HEIGHT 8

#define TAB_SIZE    4
#define TAB_SHIFT   LOWEST_SET_BIT(TAB_SIZE)
#define TAB_MASK    SET_BITS_FROM(TAB_SHIFT)

#define MAX_SCREEN_COLS (SCREEN_WIDTH/CHAR_WIDTH)
#define MAX_SCREEN_ROWS (SCREEN_HEIGHT/CHAR_HEIGHT)

#define CURSOR_SYMBOL 219

#endif/* TXT_DEF_H */
