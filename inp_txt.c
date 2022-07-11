#include <stdio.h>
#include <string.h>
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
    //fprintf(stderr, "pruneline\n");
    log->Buffer.count -= log->Lines[log->line_read].len;  // decrement Char-counter by length of 1st line
    log->Buffer.read += log->Lines[log->line_read].len;   // increment Char-read index by length of 1st line
    
    log->line_count--;                                    // decrement Line-counter by 1
    incAndWrap(log->line_read, log->max_lines);           // increment Line-read index by 1
}

void newLine(Log_t* log, byte color)
{
    //fprintf(stderr, "newline\n");
    log->line_count++;                            // increment Line-counter by 1
    incAndWrap(log->line_write, log->max_lines);  // advance Line-write index by 1

    // if adding new line exceeds max lines, prune first line
    if (log->line_count > log->max_lines)
        pruneLine(log);

    // set string pointer of next line to where \n was written
    // it should be overwritten next time a character is written
    log->Lines[log->line_write].str = &log->Buffer.str[log->Buffer.write];
    log->Lines[log->line_write].len = 0;        // next line has no chars yet
    log->Lines[log->line_write].color = color;  // continue to use same color
}

void writeLog_(Log_t* log, char* str, int len, byte color)
{
    static int delayed_newline = 0;
    //fprintf(stderr, "writelog (len == %d)\n", len);

    if (log->line_count == 0)   // first time writing to the log?
    {
        log->line_count = 1;    // initialize the first line
        log->Lines[log->line_write].str = &log->Buffer.str[log->Buffer.write];
    }

    log->Lines[log->line_read].color = color; // set color, overriding possible old color on same line

    if (len == 0) // get string length if len argument was 0
        len = strlen(str);

    if (len >= log->Buffer.size) // reject overly long string
        return;
    
    //fprintf(stderr, "pruneline loop\n");
    // as long as the string would not fit the buffer, keep pruning lines
    while (log->Buffer.count + len >= log->Buffer.size)
        pruneLine(log);

    // insert a 'queued' newline; see below
    if (delayed_newline == 1)   
    {
        //fprintf(stderr, "delayed newline\n");
        newLine(log, color);
        delayed_newline = 0;
    }

    //fprintf(stderr, "write loop\n");
    // this is where characters are actually copied to the buffer
    while (len > 0)
    {
        //fprintf(stderr, "write char\n");
        log->Buffer.str[log->Buffer.write] = *str;  // write 1 char to CharBuffer[write]
        //fprintf(stderr, "newline detection\n");
        // new line
        if (*str == '\n')
        {
            //fprintf(stderr, "detected newline!\n");
            // if the string ends with a newline, don't insert it yet, avoiding an empty line wasting space
            // instead, insert it next time this function is called
            if (len == 1)
                delayed_newline = 1;
            else
                newLine(log, color);
            //fprintf(stderr, "end of detect newline\n");
        }
        // when the character is not newline, increment all char counters
        else
        {
            log->Lines[log->line_write].len++;              // increment Line[linewrite] length by 1
            log->Buffer.count++;                            // increment Char-counter by 1
            incAndWrap(log->Buffer.write, log->Buffer.size);// advance Char-write index by 1
        }
        str++;  // increment input string pointer, in anticipation of next character being read
        len--;  // decrement remaining length
        //fprintf(stderr, "end of loop cycle\n");
    }
    ////fprintf(stderr, "x");
    //fprintf(stderr, "end of function\n");
    sprintf(debug[DEBUG_CONSOLE], "Lines: %d Write: %d Read: %d\nLineWrite len: %d, Total Chars: %d", log->line_count, log->line_write, log->line_read, log->Lines[log->line_write].len, log->Buffer.count);
}

void writeLog(Log_t* log, char* str, int len, byte color)
{
    // if string length (together with chars already on current line) exceeds maximum columns,
    // make function call itself repeatedly with smaller string slices
    
    if (len + log->Lines[log->line_write].len > log->max_cols)
    {
        //fprintf(stderr, "multiline print\n");
        // while there are still characters left
        while (len > 0)
        {
            // cap number of characters to number of available characters on current line
            int row_len = MIN(len, (log->max_cols - log->Lines[log->line_write].len));
            //fprintf(stderr, "available: %d\n", log->max_cols - log->Lines[log->line_write].len);
            //fprintf(stderr, "row_len: %d\n", row_len);
            writeLog_(log, str, row_len, color);     // write row_len characters

            if (len >= log->max_cols)   // jump to a new line after writing a full line's worth of characters
                newLine(log, color); 

            len -= row_len; // having written row_len characters, decrement remaining len by row_len
            str += row_len; // advance string pointer by row_len
        }
        if (len == 0)
            return;
    }
    else
        writeLog_(log, str, len, color);
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