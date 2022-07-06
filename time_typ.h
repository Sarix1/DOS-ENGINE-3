#ifndef TIME_TYP_H
#define TIME_TYP_H

#include "common.h"

typedef struct
{
    volatile time_t time;   // global timer
    volatile time_t seconds;// second timer
    time_t ticks;           // total game ticks
    time_t frames;          // total frames drawn
    
    int tick_rate;          // target tick rate (constant value)
    int frame_rate;         // target frame rate (constant value)
    
    time_t tick_interval;   // inferred from tick_rate
    time_t frame_interval;  // inferred from frame_rate
    time_t clock_interval;  // for PC clock

    time_t last_sec;        // lat time seconds timer was incremented
    time_t last_tick;       // last time game logic ticked ; not used anymore
    time_t last_frame;      // last time a frame was began to be drawn
    time_t last_cycle;      // last time the main loop began iterating

    time_t tick_accumulator; // Incremented by cycle duration, decremented by tick_interval
    time_t fps_count;        // Counts frames in a second so far, for FPS calculation

    int fps;      // actual measured fps
    fixp fps_avg; // average fps (frames/seconds)

} Timer_t;

#endif/* TIME_TYP_H */
