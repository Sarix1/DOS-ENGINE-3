#ifndef DRAW_H
#define DRAW_H

#include "_common.h"
#include "gfx_draw_structs.h"

void drawPixel              (int x, int y, byte color);
void drawPixels_fast        (byte* pixels, int x, int y, int w, int h);
void drawPixels             (byte* pixels, int x, int y, int w, int h);

void drawLineHorz           (int x, int y, int len, byte color);
void drawLineVert           (int x, int y, int len, byte color);
void drawLineHorz2          (int x, int y, int len, byte color);
void drawLineVert2          (int x, int y, int len, byte color);
void drawLineSlope          (int ax, int ay, int bx, int by, byte color);

void drawLine               (Vec2 p0, Vec2 p1, byte color);
void drawLineFixp           (Vec2 p0, Vec2 p1, byte color);
void drawLine_fast          (Vec2 p0, Vec2 p1, byte color);
void drawLine_fix_fast      (Vec2 p0, Vec2 p1, byte color);

void drawRectFill           (int x, int y, int w, int h, byte color);
void drawRectFill_fast      (int x, int y, int w, int h, byte color);
void drawRectFrame          (int x, int y, int w, int h, byte color);
void drawRectFrame_fast     (int x, int y, int w, int h, byte color);

void drawRectFrameRotated_v (Vec2 origin, int w, int h, Vec2 dir, byte color);

void drawCircleFill         (int x, int y, int diameter, byte color);
void drawCircleFrame        (int x, int y, int diameter, byte color);
    
void drawShape              (Vec2 pos, Vec2* points, int num_points, byte color);
void drawFixpShape          (Vec2 pos, Vec2* points, int num_points, byte color);
void drawShapeAspect        (Vec2 pos, Vec2* points, int num_points, byte color);

#include "gfx_draw_inline.h"

#endif/* DRAW_H */
