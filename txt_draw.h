#ifndef TEXT_DRAW_H
#define TEXT_DRAW_H

#include "txt_inp.h"

void drawChar8x8(int x, int y, const byte symbol, byte color, byte effect);
void drawText(int x, int y, int w, int h, const char* string, byte color, byte effect);
void drawText_fast(int x, int y, const char* string, byte color, byte effect, int len);
void drawCharSet(int x, int y, byte color, byte effect);

#endif/* TEXT_DRAW_H */
