#include <stdio.h>
#include <i86.h>
#include "common.h"
#include "input.h"
#include "sys_typ.h"
#include "txt_draw.h"

int confirm()
{
    char* str = "Continue? (Y/N)\n";
    int c;

    //if (isInit(SYS_VIDEO))
    //    drawText(0,0,0,0,str,sizeof(str)-1,COLOR_UI_TEXT,TEXT_FX_NONE);
    //else
        printf("%s\n", str);

    if (isInit(SYS_INPUT))
    {
        while (1)
        {
            delay(100);
            if (wasKeyHit(KEY_Y))
                return YES;
            if (wasKeyHit(KEY_N) || wasKeyHit(KEY_ESC))
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
