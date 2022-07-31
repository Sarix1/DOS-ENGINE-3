#ifndef DRAW2_H
#define DRAW2_H

#include <string.h>
#include "_common.h"
#include "math_fixp_inline.h"
#include "gfx_video.h"

inline byte getPixel(int x, int y)
{
    return *(g_Video.surface+(x) + Y_OFFSET(y));
}

inline void setPixel(int x, int y, byte c)
{
    *(g_Video.surface+(x) + Y_OFFSET(y)) = c;
}

inline void setPixVGA(int x, int y, byte c)
{
    *(g_Video.screen+(x) + Y_OFFSET(y)) = c;
}

inline void drawPixel(int x, int y, byte color)
{
    if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
        setPixel(x, y, color);
}

inline void drawFill(byte color)
{
    _fmemset(g_Video.surface, color, SCREEN_SIZE);
}

inline void drawLineHorz_fast(int x, int y, int len, byte color)
{
    _fmemset(g_Video.surface+(x) + Y_OFFSET(y), color, len);
}

inline void drawLineHorz2_fast(int x, int y, int len, byte color)
{
    if (len < 0)
    {
        x += len;
        len = -len;
    }
    _fmemset(g_Video.surface+(x) + Y_OFFSET(y), color, len);
}

inline void drawLineVert_fast(int x, int y, int len, byte color)
{
    byte far* pix = g_Video.surface + Y_OFFSET(y) + x;
    for (; len--; pix += SCREEN_WIDTH)
       *pix = color;
}

inline void drawLineVert2_fast(int x, int y, int len, byte color)
{
    byte far* pix;
    if (len < 0)
    {
        y += len;
        len = -len;
    }
    pix = g_Video.surface + Y_OFFSET(y) + x;
    for (; len--; pix += SCREEN_WIDTH)
       *pix = color;
}

inline void drawCopy(int x, int y, byte* source, int n)
{
    memcpy(g_Video.surface+(x) + Y_OFFSET(y), source, n);
}

inline void drawRectFrameCenter(int x, int y, int w, int h, byte color)
{
    drawRectFrame(x-(w>>1),y-(h>>1),w,h,color);
}

inline void drawRectFrameRotated(Vec2 origin, int w, int h, brad angle, byte color)
{
    drawRectFrameRotated_v(origin, w, h, newVec2_angle(angle), color);
}

#endif/* DRAW2_H */
