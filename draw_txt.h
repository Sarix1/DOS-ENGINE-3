#ifndef TEXT_DRAW_H
#define TEXT_DRAW_H

#include "txt_typ.h"

void drawChar8x8    (int x, int y, byte symbol, byte color);
void drawCharSet    (int x, int y, byte color);
int  drawText       (int x, int y, const max_cols, const max_rows, char* string, byte color);
void drawText_fast  (int x, int y, char* str, int len, byte color);
void drawInput      (int x, int y, int max_cols, InputField_t* input, byte color);
void drawLog        (int x, int y, Log_t* log);

#endif/* TEXT_DRAW_H */
