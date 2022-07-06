#ifndef VID_DEF_H
#define VID_DEF_H

#define VGA             0xA0000000l
#define VIDEO_INT       0x10

#define INPUT_STATUS    0x3DA
#define VRETRACE        0x08

#define SET_MODE        0x00
#define MODE_TEXT       0x03
#define MODE_320x200    0x13  

#define PALETTE_READ    0x03C7
#define PALETTE_WRITE   0x03C8
#define PALETTE_DATA    0x03C9
#define NUM_COLORS      256

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   200
#define SCREEN_SIZE     64000u
#define HALF_SCREEN     (SCREEN_WIDTH/2)

#if SCREEN_WIDTH == 320
#define Y_OFFSET(i) (((i)<<8)+((i)<<6))
#else
#define Y_OFFSET(i) (i*SCREEN_WIDTH)
#endif/* VID_DEF_H */

#define CHARSET_ROM    0xF000FA6EL

#endif/* VID_DEF_ */
