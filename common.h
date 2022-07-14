//#ifndef COMMON_H
//#define COMMON_H

#include "watcom.h"
#include "bits.h"
#include "status.h"
#include "colors.h"
#include "macro.h"
#include "types.h"
#include "vid_def.h"

#define DEBUG_INFO      1
#define SYSTEM_MSG      0
#define DEBUG_HITBOX    0
#define ASPECT          1

#if DEBUG_INFO == 1
#include "debug.h"
#endif

void quit();

//#endif/* COMMON_H */
