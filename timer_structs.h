#ifndef TIME_TYP_H
#define TIME_TYP_H

#include "_common.h"

typedef struct
{
    volatile time_t time;   // global timer
    volatile time_t seconds;// second timer
    volatile time_t tick_real;
    time_t tick_simulated;  // ticks that have been processed
    time_t frames;          // total frames drawn
    
    time_t tick_interval;   // inferred from tick_rate
    time_t frame_interval;  // inferred from frame_rate
    time_t clock_interval;  // for PC clock

    time_t next_sec;        // next time seconds timer it to be incremented
    time_t next_tick;       // next time game logic should ticked
    time_t next_frame;      // next time a frame should be drawn
    time_t next_clock;      // next time the PC clock interrupt was fired

    time_t fps_count;       // Counts frames in a second so far, for FPS calculation
    int ticks_per_frame;    // ticks processed before current frame
    int tick_rate;          // target tick rate (constant value)
    int frame_rate;         // target frame rate (constant value)
    int fps;                // actual measured fps
    int fps_last10[11];     // fps backlog to calculate average fps // make this work in a fucking sensible way please
    fixp fps_avg;           // average fps (frames in 10 seconds)

    byte enable_ticks;
} Timer_t;

#endif/* TIME_TYP_H */
