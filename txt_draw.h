#ifndef TEXT_DRAW_H
#define TEXT_DRAW_H

#include "txt_inp.h"

void drawChar8x8    (int x, int y, const byte symbol, byte color, byte effect);
void drawChar8x8_VGA(int x, int y, const byte symbol, const byte color);
void drawCharSet    (int x, int y, byte color, byte effect);
int  drawText       (int x, int y, int w, int h, const char* string, int len, byte color, byte effect);
void drawText_fast  (int x, int y, const char* string, int len, byte color, byte effect);
void drawText_VGA   (int x, int y, const char* string, int len, byte color, byte effect);

#endif/* TEXT_DRAW_H */
