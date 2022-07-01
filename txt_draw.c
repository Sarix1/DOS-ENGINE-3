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
    byte color_increment = (effect & TEXT_FX_GRAD) ? ((effect & TEXT_FX_FLAG) ? -1 : 1) : 0;

    for (row = 0; row < 8; row++, y++)
    {
        
        bits = charset_8x8[symbol][row];
        col = x;
        
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

void drawChar8x8_VGA(int x, int y, const byte symbol, const byte color)
{
    const byte bit1 = 1;
    int row, col;
    byte bits;

    for (row = 0; row < 8; row++, y++, col = x)
    {
        bits = charset_8x8[symbol][row];
        col = x;
        
        if (bits & bit1) setPixVGA(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixVGA(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixVGA(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixVGA(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixVGA(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixVGA(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixVGA(col, y, color); col++; bits >>= 1;
        if (bits & bit1) setPixVGA(col, y, color);
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


int drawText(int x, int y, int w, int h, const char* string, int len, byte color, byte effect)
{
    int x_offset = x;
    int newlines = 0;
    
    if (w <= 0) w = SCREEN_WIDTH-x;
    if (h <= 0) h = SCREEN_HEIGHT-y;
    
    w += x;
    h += y;
    
    if (len > 0)
    {
        while (len-- != 0)
        {
            if (*string == '\n' || x_offset > w+x)
            {
                y += 8;
                newlines++;
                if (y >= h)
                    break;
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
    else
    {
        while (*string != '\0')
        {
            if (*string == '\n' || x_offset > w+x)
            {
                y += 8;
                newlines++;
                if (y >= h)
                    break;
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

    return newlines;
}

void drawText_fast(int x, int y, const char* string, int len, byte color, byte effect)
{
    int x_offset = x;
    
    if (len > 0)
    {
        while (len-- != 0)
        {
            drawChar8x8(x_offset, y, (*string), color, effect);
            x_offset += 8;
            string++;
        }
    }
    else
    {
        while (*string != '\0')
        {
            drawChar8x8(x_offset, y, (*string), color, effect);
            x_offset += 8;
            string++;
        }
    }
}

void drawText_VGA(int x, int y, const char* string, int len, byte color, byte effect)
{
    int x_offset = x;
    
    if (len > 0)
    {
        while (len-- != 0)
        {
            drawChar8x8_VGA(x_offset, y, (*string), color);
            x_offset += 8;
            string++;
        }
    }
    else
    {
        while (*string != '\0')
        {
            drawChar8x8_VGA(x_offset, y, (*string), color);
            x_offset += 8;
            string++;
        }
    }
}
