#ifndef DEBUG_H
#define DEBUG_H

#if DEBUG_INFO == 1

#include <stdio.h>

#define DEBUG_STR_LEN 128

enum DEBUG_INDEX
{
    DEBUG_FPS,
    DEBUG_CLOCK,
    DEBUG_OBJECTS,
    DEBUG_CONSOLE,
    NUM_DEBUG
};

extern char debug[NUM_DEBUG][DEBUG_STR_LEN];

void updateStats();

#endif/* DEBUG_H */

#endif/* DEBUG_H */
