#ifndef TIME_TYP_H
#define TIME_TYP_H

#include "common.h"

typedef struct
{
    volatile time_t time;    // global timer
    volatile time_t seconds; // second timer (time/1000)
    time_t ticks;            // total game ticks
    time_t frames;           // total frames drawn
    time_t tick_time;        // target time interval of logic cycles
    time_t frame_time;       // target time interval between draws
    uint16_t tick_rate;      // target rate of logic cycles
    uint16_t frame_rate;     // target frame rate
    uint16_t fps;            // actual measured fps
    fixp   fps_avg;          // average fps (frames/seconds)
    bool running : 1;
    bool init : 1;
} Timer_t;

#endif/* TIME_TYP_H */
