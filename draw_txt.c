#include <stdio.h>
#include "common.h"
#include "timer.h"

#include "vid_def.h"
#include "draw.h"
#include "draw_txt.h"
#include "font.h"
#include "reverse.h"

#include "txt_def.h"
#include "txt_typ.h"
#include "txt_inp.h"

static const byte far* charset_rom = (byte far*)CHARSET_ROM;
static byte far* charset = charset_8x8;

enum CHARSETS
{
    CHARSET_DEFAULT,
    CHARSET_RETRO
};

void setFont(int font_id)
{
    switch (font_id)
    {
    default:
    case CHARSET_DEFAULT:
        charset = charset_rom;
        break;
    case CHARSET_RETRO:
        charset = charset_8x8;
        break;
    }
}

void drawChar8x8(int x, int y, byte symbol, byte color)
{
    int rows = 8;
    byte far* char_offset = &charset[symbol<<3];
    byte far* row_start = g_Video.surface + Y_OFFSET(y) + x;
    
    while (rows--)
    {
        byte row_pixels = reverse_byte(*(char_offset++));
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

void drawText_len(int x, int y, char* str, int len, byte color)
{
    while (len--)
    {
        drawChar8x8(x, y, *(str++), color);
        x += CHAR_WIDTH;
    }
}

void drawText_fast(int x, int y, char* str, int len, byte color)
{
    while (*str)
    {
        drawChar8x8(x, y, *(str++), color);
        x += CHAR_WIDTH;
    }
}

void drawLogLine(int x, int y, Log_t* log, Line_t* line)
{
    if (logLineEmpty(line))
        return;
    // if line string split across the end and start of the buffer, treat it as two strings
    if (line->end < line->start)
    {
        drawText_len(x, y, line->start, log->Buffer.end - line->start, line->color);
        x += CHAR_WIDTH*(log->Buffer.end - line->start);
        if (line->end != log->L_start)
            drawText_len(x, y, log->Buffer.start, line->end - log->Buffer.start, line->color);
    }
    // otherwise straightforwardly determine length by subtracting end-start pointers
    else
        drawText_len(x, y, line->start, (line->end - line->start), line->color);
}

void drawLog(int x, int y, Log_t* log)
{
    int total_lines;
    int lines_to_draw;
    Line_t* line;
    // draw background
    drawRectFill_fast(x, y, (log->max_cols * CHAR_WIDTH), (log->vis_lines * CHAR_HEIGHT), log->bg_color);
    // nothing on buffer; return
    if ((logNumChars(log)) == 0)
        return;
    // calculate how many lines to draw, and which line to begin with
    total_lines = logNumNewLines(log)+1;
    if (total_lines > log->vis_lines)
    {
        lines_to_draw = log->vis_lines;
        line = log->L_write - log->vis_lines;
        if (line < log->L_start)
            line += logMaxLines(log);
    }
    else
    {
        lines_to_draw = total_lines;
        line = log->L_read;
    }
    // draw the lines
    y += (log->vis_lines - lines_to_draw) * CHAR_HEIGHT;
    if (line > log->L_write)
    {
        while (line != log->L_end)
        {
            drawLogLine(x, y, log, line);
            y += CHAR_HEIGHT;
            line++;
        }
        line = log->L_start;
    }
    while (line <= log->L_write)
    {
        drawLogLine(x, y, log, line);
        y += CHAR_HEIGHT;
        line++;
    }
}

void drawInput(int x, int y, int max_cols, TextInput_t* input, byte color)
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
    drawText_len(x, y, input->buffer+offset, length, color);

    if ((g_Timer.ticks >> 2) & 1)
        drawChar8x8((input->cursor - offset) * CHAR_WIDTH, y, CURSOR_SYMBOL, color);
}
