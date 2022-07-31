#ifndef TIMER_DEFINES_H
#define TIMER_DEFINES_H

#define OLD_CLK_RATE_10X    182 // 18.2 Hz
#define CLOCK_RATE          1000
#define FRAME_RATE          30
#define TICK_RATE           30

#ifdef __WATCOMC__
#define TIME_KEEPER_INT     0x1C
#else
#define TIME_KEEPER_INT     0x08
#endif/* TIMER_DEFINES_H */

#define TIMER_18HZ          0
#define TIMER_1000HZ        1193

#define CONTROL_8253        0x43
#define CONTROL_WORD        0x3C
#define COUNTER_0           0x40
#define PIC1_COMMAND        0x20
#define PIC2_COMMAND        0xA0
#define PIC_EOI             0x20

#endif/* TIME_H */
