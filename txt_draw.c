#include <stdio.h>
#include "common.h"
#include "txt_draw.h"
#include "font.h"
#include "gfx.h"

void drawChar8x8(int x, int y, const byte symbol, byte color, byte effect)
{
    const byte bit1 = 1;
    int row, col;
    byte bits;
    byte color_increment = (effect & TEXT_FX_GRADIENT) ? ((effect & TEXT_FX_FLAG) ? -1 : 1) : 0;

    for (row = 0; row < 8; row++, y++)
    {
        col = x;
        bits = charset_8x8[symbol][row];
        
        if (bits & bit1) setPixel(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixel(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixel(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixel(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixel(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixel(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixel(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixel(col, y, color);

        color += color_increment;
    }
}

void drawText(int x, int y, int w, int h, const char* string, byte color, byte effect)
{
    int x_offset = x;
    w += x;
    h += y;
    while (*string != '\0' && y < h)
    {
        if (*string == '\n' || x_offset > w+x)
        {
            y += 8;
            x_offset = x;
        }
        else if (*string == '\r')
            x_offset = x;
        else if (*string == '\t')
            x_offset += 32 - (x_offset % 32);
        else
        {
            if (*string != ' ')
                drawChar8x8(x_offset, y, (*string), color, effect);
            x_offset += 8;
        }
        string++;
    }
}

void drawText_fast(int x, int y, const char* string, byte color, byte effect, int len)
{
    int x_offset = x;
    
    if (len == AUTOMATIC)
    {
        while (*string != '\0')
        {
            drawChar8x8(x_offset, y, (*string), color, effect);
            x_offset += 8;
            string++;
        }
    }
    else
    {
        while (len-- != 0)
        {
            if (*string != ' ')
                drawChar8x8(x_offset, y, (*string), color, effect);
            x_offset += 8;
            string++;
        }
    }
}

void drawCharSet(int x, int y, byte color, byte effect)
{
    int16_t row, col;
    byte i;

    i = 0;
    for (row = 0; row < 16; row++)
    {
        for (col = 0; col < 16; col++, i++)
            drawChar8x8(x+(col%16)*8, y, i, color, effect);
        y += 8;
    }
}
