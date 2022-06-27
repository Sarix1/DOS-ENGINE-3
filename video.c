#include <dos.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "malloc_.h"
#include "video.h"
#include "palette.h"

Video_t g_Video = {0};

void setVideo(byte mode)
{
	union REGS regs;
	regs.h.ah = SET_MODE;
	regs.h.al = mode;
	int86(VIDEO_INT, &regs, &regs);
}

int initVideo(byte mode)
{
    if (g_Video.init == True)
        return True;

    g_Video.frame       = 0;
    g_Video.screen      = (byte*)VGA;
    g_Video.offScreen   = (byte far*)farmalloc(SCREEN_SIZE);

	if (g_Video.offScreen != NULL)
	{
        g_Video.drawSurface = g_Video.offScreen;
        setVideo(mode);
	}
	else
	{
        g_Video.drawSurface = NULL;

        return NOT_INITIALIZED;
	}
    g_Video.init = True;

    return INITIALIZED;
}

void quitVideo()
{
    farfree(g_Video.offScreen);
    memset(g_Video.drawSurface, 0, SCREEN_SIZE);
    setVideo(MODE_TEXT);
    //resetText();
    g_Video.init = False;
}

void render()
{
	while (inportb(INPUT_STATUS) & VRETRACE)
        ;
	while (!(inportb(INPUT_STATUS) & VRETRACE))
        ;
	memcpy(g_Video.screen, g_Video.offScreen, SCREEN_SIZE);
    g_Video.frame++;
}