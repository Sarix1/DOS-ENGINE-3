//#ifndef COMMON_H
//#define COMMON_H

#define DEBUG_INFO      0
#define DEBUG_ASSERT    1
#define DEBUG_SYSTEM    0
#define DEBUG_HITBOX    0
#define ASPECT          1

#include "watcom.h"
#include "bits.h"
#include "status.h"
#include "colors.h"
#include "macro.h"
#include "types.h"
#include "vid_def.h"

#if DEBUG_INFO == 1
#include "debug.h"
#endif

void quit();

//#endif/* COMMON_H */
