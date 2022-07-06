#ifndef TEXT_DRAW_H
#define TEXT_DRAW_H

#include "txt_inp.h"

void drawChar8x8    (int x, int y, byte symbol, byte color);
void drawCharSet    (int x, int y, byte color);
int  drawText       (int x, int y, const max_cols_, const max_rows_, char* string, byte color);
void drawText_fast  (int x, const y, char* str, int len, byte color);

#endif/* TEXT_DRAW_H */
