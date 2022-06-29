#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG               1
#define DEBUG_STR_LEN       128

enum DEBUG_INDEX
{
    DEBUG_FPS,
    DEBUG_INPUT,
    DEBUG_VELOCITY,
    DEBUG_AICHASE,
    DEBUG_TESTFOV,
    DEBUG_CLOCK,
    NUM_DEBUG
};

extern char debug[NUM_DEBUG][DEBUG_STR_LEN];

#endif/* DEBUG_H */
