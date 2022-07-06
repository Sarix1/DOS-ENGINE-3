#include <stdio.h>
#include <stdarg.h>
#include "common.h"
#include "status.h"
#include "system.h"
#include "input.h"

void (*message)(const char* format, ...) = vprintf;

void statusMsg(int status)
{
    message("%s: %s\n", error_strings[ERROR], error_strings[status]);
}
/*
void message_stdout(const char* format, ...) // redundant
{
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}
*/

// freezes the game loop!!!
int prompt(char* str)
{
    int c;

    message("%s", str);

    if (isSubSysInit(SUBSYS_INPUT))
    {
        while (1)
        {
            // should read some kind of event instead of polling keymap
            if (wasKeyHit(g_Input.keymap->UI_yes))
                return YES;
            if (wasKeyHit(g_Input.keymap->UI_no))
                return NO;
        }
    }
    else
    {
        while (1)
        {
            c = getchar();
            if (c == 'y' || c == 'Y')
                return YES;
            if (c == 'n' || c == 'N' || c == '\x1b')
                return NO;
        }
    }

    return NO;
}