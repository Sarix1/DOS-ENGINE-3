#include <dos.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "malloc_.h"
#include "draw.h"
#include "maths.h"
#include "timer.h"

// no boundary check or clipping
void drawPixels_fast(byte* pixels, int x, int y, int w, int h)
{
    int row = 0;
    byte far* pix = g_Video.surface + Y_OFFSET(y) + x;
    
    while (row < h)
    {
        memcpy(pix, pixels, w);
        pix += SCREEN_WIDTH;
        pixels += w;
        row++;
    }
}

void drawPixels(byte* pixels, int x, int y, int w, int h)
{
    int row = 0;
    int row_width = w;
    int x_offset = 0;
    byte far* pix;
    
    x += g_Video.offset_x;
    y += g_Video.offset_y;
    
    // screen boundary check
    if (x < SCREEN_WIDTH && x+w >= 0 &&
        y < SCREEN_HEIGHT && y+h >= 0)
    {
        // clip edges off
        if (x < 0)
        {
            x_offset = -x;
            row_width -= x_offset;
        }
        if (x+w > SCREEN_WIDTH)
            row_width -= (x+w - SCREEN_WIDTH);
        if (y < 0)
            row = -y;
        if (y+h > SCREEN_HEIGHT)
            h -= (y+h - SCREEN_HEIGHT);
        
        pix = g_Video.surface + Y_OFFSET(y+row) + (x+x_offset);
        pixels += (w*row);
        
        while (row < h)
        {
            memcpy(pix, pixels+x_offset, row_width);
            pix += SCREEN_WIDTH;
            pixels += w;
            row++;
        }
    }
}

void drawLineHorz(int x, int y, int len, byte color)
{
    if (x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
    {
        if (x < 0)
        {
            len += x;
            x = 0;
        }
        if (len > 0)
        {
            if (x+len > SCREEN_WIDTH)
                len = SCREEN_WIDTH-x;
            drawLineHorz_fast(x, y, len, color);
        }
    }
}

void drawLineVert(int x, int y, int len, byte color)
{
    byte far* pix;

    if (x < SCREEN_WIDTH && x >= 0 && y < SCREEN_HEIGHT)
    {
        if (y < 0)
        {
            len += y;
            y = 0;
        }
        if (len > 0)
        {
            if (y+len > SCREEN_HEIGHT)
                len = SCREEN_HEIGHT-y;
            pix = g_Video.surface + Y_OFFSET(y) + x;
            for (; (len--); pix += SCREEN_WIDTH)
                *pix = color;
        }
    }
}

// allows negative length
void drawLineHorz2(int x, int y, int len, byte color)
{
    if (len < 0)
    {
        x += len;
        len = -len;
    }

    if (x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
    {
        if (x < 0)
        {
            len += x;
            x = 0;
        }
        if (len > 0)
        {
            if (x+len > SCREEN_WIDTH)
                len = SCREEN_WIDTH-x;
            drawLineHorz_fast(x, y, len, color);
        }
    }
}

// allows negative length
void drawLineVert2(int x, int y, int len, byte color)
{
    byte far* pix;

    if (len < 0)
    {
        y += len;
        len = -len;
    }

    if (x < SCREEN_WIDTH && x >= 0 && y < SCREEN_HEIGHT)
    {
        if (y < 0)
        {
            len += y;
            y = 0;
        }
        if (len > 0)
        {
            if (y+len > SCREEN_HEIGHT)
                len = SCREEN_HEIGHT-y;
            pix = g_Video.surface + Y_OFFSET(y) + x;
            for (; (len--); pix += SCREEN_WIDTH)
                *pix = color;
        }
    }
}

void drawLineSlope(int ax, int ay, int bx, int by, byte color)
{
	int i, x, y, px, py;
	
	const int dx = bx - ax;
	const int dy = by - ay;
	const int dx_abs = ABS(dx);
	const int dy_abs = ABS(dy);
	const int x_sign = SIGN(dx);
	const int y_sign = SIGN(dy);
	
	x = dy_abs >> 1;
	y = dx_abs >> 1;
	
	// Starting point
	px = ax;
	py = ay;

	if (dx_abs > dy_abs)
	{
		for (i = 0; i <= dx_abs; i++)
		{
			setPixel(px, py, color);
			y += dy_abs;
			if (y >= dx_abs)
			{
				y -= dx_abs;
				py += y_sign;
			}
			px += x_sign;
		}
	}
	else
	{
		for (i = 0; i <= dy_abs; i++)
		{
			setPixel(px, py, color);
			x += dx_abs;
			if (x >= dy_abs)
			{
				x -= dy_abs;
				px += x_sign;
			}
			py += y_sign;
		}
	}
}

void drawLine(Vec2 p0, Vec2 p1, byte color)
{
    if (clipLineToScreen(&p0, &p1) == DO_INTERSECT)
    {
        if (p0.x == p1.x)
            drawLineVert2_fast(p0.x, p0.y, (p1.y-p0.y), color);
        else if (p0.y == p1.y)
            drawLineHorz2_fast(p0.x, p0.y, (p1.x-p0.x), color);
        else
            drawLineSlope(p0.x, p0.y, p1.x, p1.y, color);
    }
}

void drawLine_fast(Vec2 p0, Vec2 p1, byte color)
{
    if (p0.x == p1.x)
        drawLineVert2_fast(p0.x, p0.y, (p1.y-p0.y), color);
    else if (p0.y == p1.y)
        drawLineHorz2_fast(p0.x, p0.y, (p1.x-p0.x), color);
    else
        drawLineSlope(p0.x, p0.y, p1.x, p1.y, color);
}

void drawLineFixp(Vec2 p0, Vec2 p1, byte color)
{
    p0 = vec2_F2I(p0);
    p1 = vec2_F2I(p1);
    //printf("%ld %ld\n", p0.x, p0.y);

    if (clipLineToScreen(&p0, &p1) == DO_INTERSECT)
    {
        if (p0.x == p1.x)
            drawLineVert2(p0.x, p0.y, (p1.y-p0.y), color);
        else if (p0.y == p1.y)
            drawLineHorz2(p0.x, p0.y, (p1.x-p0.x), color);
        else
            drawLineSlope(p0.x, p0.y, p1.x, p1.y, color);
    }
}

void drawLineFixp_fast(Vec2 p0, Vec2 p1, byte color)
{
    p0 = vec2_F2I(p0);
    p1 = vec2_F2I(p1);

    if (p0.x == p1.x)
        drawLineVert2(p0.x, p0.y, (p1.y-p0.y), color);
    else if (p0.y == p1.y)
        drawLineHorz2(p0.x, p0.y, (p1.x-p0.x), color);
    else
        drawLineSlope(p0.x, p0.y, p1.x, p1.y, color);
}

// no boundary check or clipping
void drawRectFill_fast(int x, int y, int w, int h, byte color)
{
    byte far* pix = g_Video.surface + Y_OFFSET(y) + x;
    for (; (h--); pix += SCREEN_WIDTH)
        _fmemset(pix, color, w);
}

void drawRectFill(int x, int y, int w, int h, byte color)
{
    byte far* pix;

    if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
    {
        if (y < 0)
        {
            h += y;
            y = 0;
        }
        if (h > 0)
        {
            if (x < 0)
            {
                w += x;
                x = 0;
            }
            if (w > 0)
            {
                if (x+w > SCREEN_WIDTH)
                    w = SCREEN_WIDTH-x;
                if (y+h > SCREEN_HEIGHT)
                    h = SCREEN_HEIGHT-y;
                pix = g_Video.surface + Y_OFFSET(y) + x;
                for (; (h--); pix += SCREEN_WIDTH)
                    _fmemset(pix, color, w);
            }
        }
    }
}

void drawRectFrame(int x0, int y0, int w, int h, byte color)
{
    byte sides = 0x0F;  byte far* pix;  int x1, y1, i;
    if ( x0 >= SCREEN_WIDTH || y0 >= SCREEN_HEIGHT
        || (x1=x0+w) < 0    || (y1=y0+h) < 0 )
        return;

    if (x0 < 0)             { sides &= ~OUTCODE_LEFT;   x0 = 0;             }
    if (x1 > SCREEN_WIDTH)  { sides &= ~OUTCODE_RIGHT;  x1 = SCREEN_WIDTH;  }
    if (y0 < 0)             { sides &= ~OUTCODE_TOP;    y0 = 0;             }
    if (y1 > SCREEN_HEIGHT) { sides &= ~OUTCODE_BOTTOM; y1 = SCREEN_HEIGHT; }
    if (!sides) // if sides are in orbit, you must die
        return;

    pix = g_Video.surface + Y_OFFSET(y0) + x0;
    w = x1-x0;
    h = y1-y0;
    if (sides & OUTCODE_TOP)    _fmemset(pix,               color, w);
    if (sides & OUTCODE_BOTTOM) _fmemset(pix+Y_OFFSET(h-1), color, w);
    if (sides & OUTCODE_LEFT)
    {
        if (sides & OUTCODE_RIGHT)
        {
            byte far* pix2 = pix + w-1;
            for (i=0; i < h-2; i++) {
                pix += SCREEN_WIDTH;
                pix2 += SCREEN_WIDTH;
                *pix2 = *pix = color;
            }
        }
        else
        {
            for (i=0; i < h-2; i++) {
                pix += SCREEN_WIDTH;
                *pix = color;
            }
        }
    }
    else if (sides & OUTCODE_RIGHT)
    {
        pix += w-1;
        for (i=0; i < h-2; i++) {
            pix += SCREEN_WIDTH;
            *pix = color;
        }
    }
}

void drawRectFrame_fast(int x, int y, int w, int h, byte color)
{
    int i;
    byte far* pix = g_Video.surface + Y_OFFSET(y) + x;

    _fmemset(pix, color, w);
    if (h > 1)
    {
        byte far* pix2 = pix + w-1;
        for (i = 1; i < h-1; i++)
        {
            pix += SCREEN_WIDTH;
            pix2 += SCREEN_WIDTH;
            *pix2 = *pix = color;
        }
        pix += SCREEN_WIDTH;
        _fmemset(pix, color, w);
    }
}

void drawRectFrameRotated_v(Vec2 origin, int w, int h, Vec2 dir, byte color)
{

    Vec2 vw = vec2_F2I(vec2scale(dir,              toFixp(w)));
    Vec2 vh = vec2_F2I(vec2scale(vec2_90left(dir), toFixp(h)));
    Vec2 p0 = vec2add3(origin, vw,          vh          );
    Vec2 p1 = vec2add3(origin, vw,          vec2inv(vh) );
    Vec2 p2 = vec2add3(origin, vec2inv(vw), vec2inv(vh) );
    Vec2 p3 = vec2add3(origin, vec2inv(vw), vh          );

    p0.y = a(p0.y);
    p1.y = a(p1.y);
    p2.y = a(p2.y);
    p3.y = a(p3.y);

    drawLine(p0,p1,color);
    drawLine(p1,p2,color);
    drawLine(p2,p3,color);
    drawLine(p3,p0,color);
}

void drawCircleFill(int x, int y, int diameter, byte color)
{
    const byte far* center = g_Video.surface + Y_OFFSET(y) + x;
    const int radius       = (diameter >> 1) + 1;
    const int remainder    = diameter & 1;
    const int r_offset     = Y_OFFSET(remainder^1);
    const fixp inv_radius  = FIX_ONE / (radius == 0 ? 1 : radius);
    fixp y_scale_factor    = 0;
    // offsets
    int dx = radius-1;
    int dy = 0;
    int dy_offset = Y_OFFSET(dy);
    int width = (dx << 1) + remainder;
	
    if (diameter != 0)
    {
        if (remainder)
            goto draw_circle_fill_lower;
        while (dy < radius)
        {
            dy_offset = Y_OFFSET(dy);
            width = (dx << 1) + remainder;
            _fmemset(center - dy_offset-dx, color, width);
            dy_offset -= r_offset;

        draw_circle_fill_lower:
            _fmemset(center + dy_offset-dx, color, width);
            y_scale_factor += inv_radius;
            dx = toInt(radius * fixpSinAcos(y_scale_factor));
            dy++;
        }
    }
}

void drawCircleFrame(int x, int y, int diameter, byte color)
{
    const byte far* center  = g_Video.surface + Y_OFFSET(y-1) + x-1;
    const int radius        = (diameter >> 1);
    const int not_remainder = ~(diameter & 1);
    const fixp inv_radius    = FIX_ONE / (radius == 0 ? 1 : radius);
    fixp y_scale_factor      = 0;
    // offsets
    byte far* pix = center;
    int dx = radius-1;
    int dy = 0;
    int dx_offset;
    int dy_offset;

    if (diameter != 0)
    {
        while (dy <= dx)
        {
            dx_offset = Y_OFFSET(dx);
            dy_offset = Y_OFFSET(dy);

            // top left quadrant
            *(pix-dy-dx_offset) = color;    // top left
            *(pix-dx-dy_offset) = color;    // left upper
            // top right quadrant
            pix -= not_remainder;
            *(pix+dy-dx_offset) = color;    // top right
            *(pix+dx-dy_offset) = color;    // right upper
            // bottom right quadrant
            pix -= Y_OFFSET(not_remainder);
            *(pix+dx+dy_offset) = color;    // right lower
            *(pix+dy+dx_offset) = color;    // bottom right
            // bottom left quadrant
            pix += not_remainder;
            *(pix-dx+dy_offset) = color;    // left lower
            *(pix-dy+dx_offset) = color;    // bottom left

            pix = center;
            y_scale_factor += inv_radius;
            dx = toInt(radius * fixpSinAcos(y_scale_factor));
            dy++;
        }
    }
}

// should go to visible.c ... maybe? make decision later
void drawVisible(int x, int y, Visible_t* vis)
{
    drawPixels(vis->pixels, x, y, vis->sprite->w, vis->sprite->h);
    
    if (g_Timer.ticks % vis->frame_interval == 0)
    {
        vis->frame++;
        if (vis->frame < vis->sprite->num_frames)
            vis->pixels += vis->sprite->size;
        else
        {
            vis->pixels = vis->sprite->pixels;
            vis->frame = 0;
        }
    }
}

void drawShape(Vec2 pos, Vec2* points, int num_points, byte color)
{
    int i;
    for (i=0; i < num_points-1; i++)
        drawLine( vec2add(points[i], pos),  vec2add(points[i+1], pos),  color );

    drawLine( vec2add(points[i], pos),  vec2add(points[0], pos), color );
}

void drawFixpShape(Vec2 pos, Vec2* points, int num_points, byte color)
{
    int i;
    for (i=0; i < num_points-1; i++)
        drawLineFixp( vec2add(points[i],pos),  vec2add(points[i+1],pos),   color );

    drawLineFixp( vec2add(points[i],pos),  vec2add(points[0],pos),  color );
}

// draw shape with aspect ratio correction
void drawShapeAspect(Vec2 pos, Vec2* points, int num_points, byte color)
{
    int i;
    Vec2 a, b, first;

    first.x = b.x = pos.x + points[0].x;
    first.y = b.y = pos.y + fixpMul((points[0].y), (FIX_ONE*5)/6);
    
    for (i=0; i < num_points-1; i++)
    {
        a = b;
        b.x = pos.x + points[i+1].x;
        b.y = pos.y + fixpMul((points[i+1].y), (FIX_ONE*5)/6);

        drawLine(a, b, color);
    }
    drawLine(b, first, color);
}

// jittery version
/*
void drawShapeAspect(Vec2 pos, Vec2* points, int num_points, byte color)
{
    int i;
    Vec2 a, b, first;
    first.x = b.x = points[0].x + pos.x;
    first.y = b.y = fixpMul((points[0].y + pos.y), ((FIX_ONE*5)/6));

    for (i=0; i < num_points-1; i++)
    {
        a = b;
        b.x = points[i+1].x + pos.x;
        b.y = fixpMul((points[i+1].y + pos.y), ((FIX_ONE*5)/6));

        drawLine(a, b, color);
    }
    drawLine(b, first, color);
}
*/