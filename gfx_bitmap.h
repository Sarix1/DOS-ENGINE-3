#ifndef BITMAP_H
#define BITMAP_H

#include "_common.h"

#define LOAD_PALETTE 1
#define LOAD_IMAGE   2

typedef struct
{   
    byte* data;
    byte palette[768];
    uint16_t w, h;
} Bitmap_t;

void loadBitmap(Bitmap_t* b, char* filename, flags_t flags);
void freeBitmap(Bitmap_t* bmp);
void drawBitmap(Bitmap_t* bmp, int x, int y);
void convertFont8x8(char* bmp_filename, char* output_filename);

#endif/* BITMAP_H */
