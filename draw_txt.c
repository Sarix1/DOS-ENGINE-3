#include <stdio.h>
#include "common.h"
#include "draw_txt.h"
#include "txt_def.h"
#include "txt_typ.h"
#include "vid_def.h"
#include "reverse.h"
#include "timer.h"
#include "font.h"
#include "draw.h"

static const byte far* charset_rom = (byte far*)CHARSET_ROM;

//static byte far* charset = (byte far*)CHARSET_ROM; ////
static byte far* charset = charset_8x8;

void drawChar8x8(int x, int y, byte symbol, byte color)
{
    int rows = 8;
    byte far* char_offset = &charset[symbol<<3];
    byte far* row_start = g_Video.surface + Y_OFFSET(y) + x;
    
    while (rows--)
    {
        byte row_pixels = reverse_bits(*(char_offset++));
        byte far* pix = row_start;

        while (row_pixels)
        {
            if (row_pixels & 0x80)
                *pix = color;

            row_pixels <<= 1;
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

int drawText(int x, int y, const max_cols, const max_rows, char* string, byte color)
{
    const x_start = x;
    int rows, cols;
    int newlines = 0;
    int col = 0;
    char c;

    if ((cols = MAX_SCREEN_COLS - x/CHAR_WIDTH)  <= 0)  return 0;
    if ((rows = MAX_SCREEN_ROWS - y/CHAR_HEIGHT) <= 0)  return 0;
    cols = (max_cols == 0) ? cols : MIN(max_cols, cols);
    rows = (max_rows == 0) ? rows : MIN(max_rows, rows);
    
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
            y += CHAR_HEIGHT;
        case '\r':
            col = 0;
            x = x_start;
            continue;
            
        // TAB
        case '\t':
            col = (col & ~TAB_MASK) + TAB_SIZE;
            if (col >= cols)
                goto drawText_newline;
            x += (TAB_SIZE*CHAR_WIDTH);
            continue;
        // 1 char
        default:
            drawChar8x8(x,y,c,color);
        case ' ':
            if (++col >= cols)
                goto drawText_newline;
            x += CHAR_WIDTH;
        }
    }
    return newlines;
}

void drawText_fast(int x, int y, char* str, int len, byte color)
{
    if (len == 0)
    {
        while (*str)
        {
            drawChar8x8(x, y, *(str++), color);
            x += CHAR_WIDTH;
        }
        return;
    }

    while (len--)
    {
        drawChar8x8(x, y, *(str++), color);
        x += CHAR_WIDTH;
    }
    return;
}

void drawLog(int x, int y, Log_t* log)
{
    int line, num_lines;
    // draw background
    drawRectFill_fast(x, y,
        (log->max_cols * CHAR_WIDTH),
        (log->vis_lines * CHAR_HEIGHT),
        log->bg_color);

    // determine which line to start with, how many to draw
    if (log->line_count > log->vis_lines)
    {
        num_lines = log->vis_lines;
        line = log->line_read + (log->line_count - log->vis_lines);
        if (line >= log->max_lines)
            line -= log->max_lines;
    }
    else
    {
        num_lines = log->line_count;
        line = log->line_read;
    }
    
    // draw lines
    if (log->line_count == 0)
        return;

    x = 0;
    y += (log->vis_lines - num_lines) * CHAR_HEIGHT;

    do {
        drawText_fast(x, y,
            log->Lines[line].str,
            log->Lines[line].len,
            log->Lines[line].color);

        incAndWrap(line, log->max_lines);
        y += CHAR_HEIGHT;
    } while (rDecAndWrap(line, log->max_lines) != log->line_write);
}

void drawInput(int x, int y, int max_cols, InputField_t* input, byte color)
{
    int length, offset;
    // draw background
    drawRectFill_fast(x, y, max_cols * CHAR_WIDTH, CHAR_HEIGHT, COLOR_INPUT_BG);
    // clip text to edges
    if (input->cursor >= max_cols)
        offset = input->cursor - (max_cols-1);
    else
        offset = 0;

    length = (input->length < max_cols) ? input->length : max_cols-1;
    drawText_fast(x, y, input->buffer+offset, length, color);

    if ((g_Timer.ticks >> 2) & 1)
        drawChar8x8((input->cursor - offset) * CHAR_WIDTH, y, CURSOR_SYMBOL, color);
}
