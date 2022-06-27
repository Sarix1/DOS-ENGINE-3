#include "input.h"
#include "keys.h"

inline char keyToAscii(byte keycode)
{
    char c;
    if (keycode < 128)
    {
        if ((isKeyDown(KEY_LSHIFT) | isKeyDown(KEY_RSHIFT)) ^ g_Input.caps_lock)
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

inline void cursorLeft(TextField_t* text)
{
    if (text->cursor > text->start)
        text->cursor--;
}

inline void cursorRight(TextField_t* text)
{
    if (text->cursor < text->length)
        text->cursor++;
}

inline void writeChar(TextField_t* text, char c) // inline
{
    if (text->length < text->capacity)
    {
        if (text->cursor < text->length)
        {
            int i;
            for (i = text->length; i > text->cursor; i--)
                text->buffer[i] = text->buffer[i-1];
        }
        text->buffer[text->cursor] = c;
        text->cursor++;
        text->length++;
    }
}

// could be a generalized function accepting cursor, length, buffer, start as arguments
inline void eraseChar(TextField_t* text)
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
    }
}

int textInput(TextField_t* text, byte keycode)
{   
    byte c;

    if (keycode == KEY_ESC)
        g_Input.text_input = 0;
    else if (keycode == KEY_CAPSLOCK)
        g_Input.caps_lock ^= 1;
    else if (keycode == KEY_LEFT)
        cursorLeft(text);
    else if (keycode == KEY_RIGHT)
        cursorRight(text);
    else if (keycode == KEY_BACKSPACE)
        eraseChar(text);
    else if (keycode == KEY_ENTER || keycode == KEY_PAD_ENTER)
    {
        if (isKeyDown(KEY_LSHIFT) || isKeyDown(KEY_RSHIFT))
            writeChar(text, '\n');
        else
            g_Input.text_enter = 1;
    }
    else if (c = keyToAscii(keycode))
        writeChar(text, c);
    else
        return NOT_HANDLED;

    return HANDLED;
}