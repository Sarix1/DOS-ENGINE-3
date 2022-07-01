#ifndef GFX_H
#define GFX_H

#include <string.h>
#include "common.h"
#include "video.h"
#include "gfx_typ.h"

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

inline void drawFill(byte color)
{
    memset(g_Video.surface, color, SCREEN_SIZE);
}

inline void drawLineHorz_fast(int x, int y, int len, byte color)
{
    memset(g_Video.surface+(x) + Y_OFFSET(y), color, len);
}

inline void drawLineHorz2_fast(int x, int y, int len, byte color)
{
    if (len < 0)
    {
        x += len;
        len = -len;
    }
    memset(g_Video.surface+(x) + Y_OFFSET(y), color, len);
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

inline void drawPixel(int x, int y, byte color)
{
    if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
        setPixel(x, y, color);
}

//void drawPixel          (int x, int y, byte color);
void drawPixels_fast    (byte* pixels, int x, int y, int w, int h);
void drawPixels         (byte* pixels, int x, int y, int w, int h);
void drawLineHorz       (int x, int y, int len, byte color);
void drawLineVert       (int x, int y, int len, byte color);
void drawLineHorz2      (int x, int y, int len, byte color);
void drawLineVert2      (int x, int y, int len, byte color);
void drawLineSlope      (int ax, int ay, int bx, int by, byte color);
void drawLine           (Vec2 p0, Vec2 p1, byte color);
void drawLineFixp       (Vec2 p0, Vec2 p1, byte color);
void drawLine_fast      (Vec2 p0, Vec2 p1, byte color);
void drawLine_fix_fast  (Vec2 p0, Vec2 p1, byte color);
void drawRectFill       (int x, int y, int w, int h, byte color);
void drawRectFill_fast  (int x, int y, int w, int h, byte color);
void drawRectFrame      (int x, int y, int w, int h, byte color);
void drawRectFrame_fast (int x, int y, int w, int h, byte color);
void drawCircleFill     (int x, int y, int diameter, byte color);
void drawCircleFrame    (int x, int y, int diameter, byte color);
//void drawVisible(Visible_t* vis, int x, int y)
void drawShape          (Vec2 pos, Vec2* points, int num_points, byte color);
void drawFixpShape      (Vec2 pos, Vec2* points, int num_points, byte color);
void drawShapeScreen    (Vec2 pos, Vec2* points, int num_points, byte color);
#endif/* GFX_H */
