#include <dos.h>
#include <stdio.h>
#include <string.h>
#include "_common.h"
#include "gfx_video.h"
#include "gfx_palette.h"
#include "_malloc.h"

Video_t g_Video = {0};

static void setVideo(byte mode)
{
	union REGS regs;
	regs.h.ah = SET_MODE;
	regs.h.al = mode;
	int86(VIDEO_INT, &regs, &regs);
}

int initVideo()
{
    g_Video.screen     = (byte*)VGA;
    g_Video.off_screen = (byte far*)farmalloc(SCREEN_SIZE);

	if (g_Video.off_screen != NULL)
	{
        g_Video.surface = g_Video.off_screen;
        setVideo(MODE_320x200);
	}
	else
	{
        g_Video.surface = NULL;
        quitVideo();

        return ERROR_MEMORY;
	}

    return SUCCESS;
}

int quitVideo()
{
    if (g_Video.off_screen != NULL)
        farfree(g_Video.off_screen);

    memset(VGA, 0, SCREEN_SIZE);
    setVideo(MODE_TEXT);

    return SUCCESS;
}

void render()
{
	while (inportb(INPUT_STATUS) & VRETRACE)
        ;
	while ((inportb(INPUT_STATUS) & VRETRACE) == 0)
        ;
	memcpy(g_Video.screen, g_Video.off_screen, SCREEN_SIZE);
    memset(g_Video.off_screen, 0, SCREEN_SIZE);
}
