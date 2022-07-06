#ifndef TXT_DEF_H
#define TXT_DEF_H

#include "macro.h"
#include "vid_def.h"

#define CHAR_SIZE       8
#define CHAR_SHIFT      LOWEST_SET_BIT(CHAR_SIZE)

#define TAB_SIZE        4
#define TAB_SHIFT       LOWEST_SET_BIT(CHAR_SIZE)
#define TAB_MASK        SET_BITS_FROM(TAB_SHIFT)

#endif/* TXT_DEF_H */
