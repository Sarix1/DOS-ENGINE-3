#include <stdio.h>
#include "common.h"
#include "inp_txt.h"
#include "txt_def.h"
#include "txt_typ.h"
#include "input.h"

char far format_buffer[FORMAT_BUFFER_SIZE] = {0};

int strcmptok(char* str, char* token, char delim)
{
    int index = 0; // position in str
    // skip delimeter character(s) in the beginning
    while (*str == delim)
    {
        str++;
        index++;
    }
    // compare str and token
    while (*str == *token)
    {
        // end of token reached and strings were identical;
        // return index in str where the token string ends ('\0')
        if (*token == '\0')
            return index;

        *str++;
        *token++;
        index++;
    }
    // when the strings diverge, return -1 (token not found)
    return -1;
}

static inline char keyToAscii(byte keycode)
{
    byte c;
    if (keycode < 128)
    {
        if ((isKeyDown(KEY_LSHIFT) | isKeyDown(KEY_RSHIFT)) ^ (g_Input.flags & INPUT_FLAG_CAPS))
            c = ascii_shifted[keycode];
        else
            c = ascii[keycode];
    }
    else
        c = ascii_special[keycode & 0x7F];
    // return a character if the keycode corresponds to a valid ASCII code
    if ((c >= 32 && c < 128) || c == '/')
        return c;
    
    return 0;
}

void pruneLine(Log_t* log)
{
    if (log->line_count > 0)
    {
        int len = log->Lines[log->line_read].len;
        log->Buffer.count -= len+1;

        incAndWrap(log->line_read, log->max_lines);
        log->line_count--;

        if (log->line_count > 0)
            log->Buffer.str = log->Lines[log->line_read].str;
    }
}

void newLine(Log_t* log, byte color)
{
    if (++log->line_count >= log->max_lines)
        pruneLine(log);

    log->Lines[log->line_write].str = &log->Buffer.str[log->Buffer.write];
    log->Lines[log->line_write].len = 0;
    log->Lines[log->line_write].color = color;
}

void writeLog(Log_t* log, char* str, int len, byte color)
{
    static int delayed_newline = 0;

    if (log->line_count == 0)
        log->line_count = 1;

    while (log->Buffer.count + len+1 >= log->Buffer.size)
        pruneLine(log);

    if (delayed_newline)
    {
        newLine(log, color);
        delayed_newline = 0;
    }

    // redirect to multi-line function here

    while (len--)
    {
        char c = *str++;
        putcBuf(&log->Buffer, c);

        if (c == '\n')
        {
            if (len == 0)
            {
                delayed_newline = 1;
                continue;
            }
            newLine(log, color);
        }
        else
            log->Lines[log->line_write].len++;
    }
    sprintf(debug[DEBUG_CONSOLE], "Lines: %d Write: %d Read: %d\nLineWrite len: %d, Total Chars: %d", log->line_count, log->line_write, log->line_read, log->Lines[log->line_write].len, log->Buffer.count);
}

void v_writeLog_f(Log_t* log, byte color, char* format, va_list args)
{
    int len = vsnprintf(format_buffer, FORMAT_BUFFER_SIZE, format, args);
    writeLog(log, format_buffer, len, color);
}

void writeLog_f(Log_t* log, byte color, char* format, ...)
{
    va_list args;
    va_start(args, format);
    v_writeLog_f(log, color, format, args);
    va_end(args);
}

// InputField_t

void resetInput(InputField_t* input)
{
    input->buffer[0] = '\0';
    input->length = 0;
    input->cursor = 0;
    input->start = 0;
}

static inline void cursorLeft(InputField_t* text)
{
    if (text->cursor > text->start)
        text->cursor--;
}

static inline void cursorRight(InputField_t* text)
{
    if (text->cursor < text->length-1)
        text->cursor++;
}

static inline void writeChar(InputField_t* text, byte c) // inline
{
    if (text->length < text->capacity-1)
    {
        if (text->cursor < text->length)
        {
            int i;
            for (i = text->length; i > text->cursor; i--)
                text->buffer[i] = text->buffer[i-1];
        }
        text->buffer[text->cursor] = c;
        text->buffer[++text->cursor] = '\0';
        text->length++;
    }
}

static inline void eraseChar(InputField_t* text)
{
    if (text->cursor > text->start)
    {
        if (text->cursor < text->length)
        {
            int i;
            for (i = text->cursor; i < text->length; i++)
                text->buffer[i-1] = text->buffer[i];
        }
        text->cursor--;
        text->length--;
        text->buffer[text->length] = '\0';
    }
}

int handleTextInput(InputEvent_t event)
{   
    byte c;

    if (event.type == KEYSTATE_RELEASED)
        return NOT_HANDLED;

    switch (event.keycode)
    {
    case KEY_CAPSLOCK:
        g_Input.flags ^= INPUT_FLAG_CAPS;
        break;
    case KEY_LEFT:
        cursorLeft(g_Input.input_field);
        break;
    case KEY_RIGHT:
        cursorRight(g_Input.input_field);
        break;
    case KEY_BACKSPACE:
        eraseChar(g_Input.input_field);
        break;
    case KEY_ENTER:
    case KEY_PAD_ENTER:
        if (isKeyDown(KEY_LSHIFT) || isKeyDown(KEY_RSHIFT))
            writeChar(g_Input.input_field, '\n');
        else
            g_Input.input_callback(g_Input.input_field);
        break;
    default:
        if (c = keyToAscii(event.keycode))
            writeChar(g_Input.input_field, c);
        else
            return NOT_HANDLED;
    }

    return HANDLED;
}