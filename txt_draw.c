#include <stdio.h>
#include "common.h"
#include "txt_draw.h"
#include "txt_def.h"
#include "vid_def.h"
#include "font.h"
#include "gfx.h"

static const byte far* charset_rom = (byte far*)CHARSET_ROM;

static byte far* charset = charset_8x8;//(byte far*)CHARSET_ROM;

void drawChar8x8(int x, int y, byte symbol, byte color)
{
    int rows = 8;
    byte far* char_offset = &charset[symbol<<3];
    byte far* row_start = g_Video.surface + Y_OFFSET(y) + x;
    
    while (rows--)
    {
        byte row_pixels = *(char_offset++);
        byte far* pix = row_start;

        while (row_pixels)
        {
            if (row_pixels & 1)
                *pix = color;

            row_pixels >>= 1;
            pix++;
        }

        row_start += SCREEN_WIDTH;
    }
}

void drawCharSet(int x, int y, byte color)
{
    int16_t row, col;
    byte i;

    i = 0;
    for (row = 0; row < 16; row++)
    {
        for (col = 0; col < 16; col++, i++)
            drawChar8x8(x+(col%16)*8, y, i, color);
        y += 8;
    }
}

int drawText(int x, int y, const max_cols_, const max_rows_, char* string, byte color)
{
    const x_start = x;
    int rows, cols;
    int newlines = 0;
    int col = 0;
    char c;

    if ((cols = (SCREEN_WIDTH /CHAR_SIZE) - (x>>CHAR_SHIFT)) <= 0)  return 0;
    if ((rows = (SCREEN_HEIGHT/CHAR_SIZE) - (y>>CHAR_SHIFT)) <= 0)  return 0;
    cols = (max_cols_ == 0) ? cols : MIN(max_cols_, cols);
    rows = (max_rows_ == 0) ? rows : MIN(max_rows_, rows);
    
    while (c = *(string++))
    {
        switch (c)
        {     
        // CRLF
        case '\n':
            drawText_newline:
            newlines++;
            if (--rows == 0)
                return newlines;
            y += CHAR_SIZE;
        case '\r':
            col = 0;
            x = x_start;
            continue;
            
        // TAB
        case '\t':
            col = (col & ~TAB_MASK) + TAB_SIZE;
            if (col >= cols)
                goto drawText_newline;
            x += (TAB_SIZE*CHAR_SIZE);
            continue;
        // 1 char
        default:
            drawChar8x8(x,y,c,color);
        case ' ':
            if (++col >= cols)
                goto drawText_newline;
            x += CHAR_SIZE;
        }
    }
    return newlines;
}

void drawText_fast(int x, const y, char* str, int len, byte color)
{
    if (len == 0)
    {
        while (*str)
        {
            drawChar8x8(x, y, *(str++), color);
            x += CHAR_SIZE;
        }
        return;
    }

    while (len--)
    {
        drawChar8x8(x, y, *(str++), color);
        x += CHAR_SIZE;
    }
    return;
}
