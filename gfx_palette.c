//#include <dos.h>
#include <conio.h>
#include "_common.h"
#include "gfx_palette.h"
#include "gfx_video_defines.h"
#include "math_fixp_inline.h"

void setVGAPalette(Palette_t* pal)
{
    unsigned i;
    outp(PALETTE_WRITE, 0);
    for (i = 0; i < 256; i++)
    {
       outp(PALETTE_DATA, pal->colors[i].r>>2);
       outp(PALETTE_DATA, pal->colors[i].g>>2);
       outp(PALETTE_DATA, pal->colors[i].b>>2);
    }
}

void getVGAPalette(Palette_t* pal)
{
    unsigned i;
    outp(PALETTE_READ, 0);
    for (i = 0; i < 256; i++)
    {
       pal->colors[i].r = (inp(PALETTE_DATA))<<2;
       pal->colors[i].g = (inp(PALETTE_DATA))<<2;
       pal->colors[i].b = (inp(PALETTE_DATA))<<2;
    }
}

void setVGAPaletteColor_RGB(byte index, byte red, byte green, byte blue)
{
    outp(PALETTE_WRITE, index);
    outp(PALETTE_DATA,  (red  >>2));
    outp(PALETTE_DATA,  (green>>2));
    outp(PALETTE_DATA,  (blue >>2));
}

void setVGAPaletteColor(byte index, Color_t color)
{
    setVGAPaletteColor_RGB(index, color.r, color.g, color.b);
}

Color_t getPaletteColor_VGA(byte index)
{
    Color_t color;
    outp(PALETTE_READ, index);
    color.r = inp(PALETTE_DATA)<<2;
    color.g = inp(PALETTE_DATA)<<2;
    color.b = inp(PALETTE_DATA)<<2;

    return color;
}

void setPaletteColor_RGB(Palette_t* pal, byte index, byte r, byte g, byte b)
{
    pal->colors[index].r = r;
    pal->colors[index].g = g;
    pal->colors[index].b = b;
}

void setPaletteColor(Palette_t* pal, byte index, Color_t color)
{
    pal->colors[index] = color;
}

Color_t getPaletteColor(Palette_t* pal, byte index)
{
    return pal->colors[index];
}

void scalePalette(Palette_t* pal, fixp scale)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        pal->colors[i].r = (pal->colors[i].r*scale) >> FIXP_SHIFT;
        pal->colors[i].g = (pal->colors[i].g*scale) >> FIXP_SHIFT;
        pal->colors[i].b = (pal->colors[i].b*scale) >> FIXP_SHIFT;
    }
}

void setWholePalette(Palette_t* pal, byte r, byte g, byte b)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        pal->colors[i].r = r;
        pal->colors[i].g = g;
        pal->colors[i].b = b;
    }
}

void fadeToBlack()
{
    int i, j;
    fixp scale = FIXP_ONE;
    Palette_t pal;
    getVGAPalette(&pal);

    for (i = 0; i < 256; i++)
    {
        scale -= (FIXP_ONE/256);
        for (j = 0; j < 256; j++)
        {
            setVGAPaletteColor_RGB(j,
            (pal.colors[j].r*scale) >> FIXP_SHIFT,
            (pal.colors[j].g*scale) >> FIXP_SHIFT,
            (pal.colors[j].b*scale) >> FIXP_SHIFT);
        }
        //delay(0.5);
    }
}

void fadeFromBlack()
{
    int i, j;
    fixp scale = 0;
    Palette_t pal;
    getVGAPalette(&pal);

    for (i = 0; i < 256; i++)
    {
        scale += (FIXP_ONE/256);
        for (j = 0; j < 256; j++)
        {
            setVGAPaletteColor_RGB(j,
            (pal.colors[j].r*scale) >> FIXP_SHIFT,
            (pal.colors[j].g*scale) >> FIXP_SHIFT,
            (pal.colors[j].b*scale) >> FIXP_SHIFT);
        }
        //delay(0.5);
    }
}

void rotatePaletteLeft(Palette_t* pal)
{
    Color_t temp = pal->colors[0];
    unsigned i;
    for (i = 0; i < 256; i++)
        pal->colors[i] = pal->colors[i+1];
    pal->colors[255] = temp;
}

void rotatePaletteRight(Palette_t* pal)
{
    Color_t temp = pal->colors[255];
    unsigned i;
    for (i = 255; i > 0; i--)
        pal->colors[i] = pal->colors[i-1];
    pal->colors[0] = temp;
}

void rotatePaletteLeftBy(Palette_t* pal, const unsigned n_first, const unsigned first, const unsigned stop)
{
    if (n_first == first || n_first == stop)
        return;

    {
        unsigned read = n_first;
        unsigned write = first;
        unsigned saved = first;

        while (read != stop)
        {
            Color_t temp = pal->colors[write];
            pal->colors[write] = pal->colors[read];
            pal->colors[read] = temp;
            if (write == saved)
                saved = read;
            write++; read++;
        }
        rotatePaletteLeftBy(pal, saved, write, stop);
    }
}

// CRITICAL ISSUE -- causes stack overflow on n == 1
// write unit test for palette rotations !
void rotatePalette(Palette_t* pal, const int n, const unsigned first, const unsigned end)
{
    if (n < 0)
        rotatePaletteLeftBy(pal, first-n, first, end);
    else if (n > 0)
        rotatePaletteLeftBy(pal, end-n, first, end);
}

byte findNearest(Palette_t* pal, Color_t color)
{
    int i;
    byte nearest_index = 0;
    uint32_t smallest_distance = UINT32_MAX;

    for (i = 0; i < 256; i++)
    {
        uint32_t distance = // measure the squared distance (a^2 + b^2 + c^2)
            square((int16_t)pal->colors[i].r - color.r) +
            square((int16_t)pal->colors[i].g - color.g) +
            square((int16_t)pal->colors[i].b - color.b);

        // update nearest color if smaller distance found
        if (distance < smallest_distance)
        {
            // stop the loop if we find the exact same color
            if (distance == 0)
                return i;

            nearest_index = i;
            smallest_distance = distance;
        }
    }

    return nearest_index;
}

// linearly interpolates between two colours; start and end
// writes the results to an offset in an array of colors, pointed to by *gradient
// num_colors will be written, with start at *gradient, and end at *gradient + num_colors-1
int buildGradient(Color_t start, Color_t end, Color_t* gradient, int num_colors)
{
    int i;
    fixp r,g,b, delta_r, delta_g, delta_b, denominator, half_denom;

    if (num_colors <= 0 || gradient == NULL)
        return ERROR; // failure

    if (num_colors == 1)
    {
        gradient[0].r = ((uint16_t)start.r+end.r+1) >> 1;
        gradient[0].g = ((uint16_t)start.g+end.g+1) >> 1;
        gradient[0].b = ((uint16_t)start.b+end.b+1) >> 1;

        return SUCCESS; // success
    }

    if (num_colors == 2)
    {
        gradient[0] = start;
        gradient[1] = end;

        return SUCCESS; // success
    }

    if (start.r == end.r &&
        start.g == end.g &&
        start.b == end.b)
    {
        for (i = 0; i < num_colors; i++)
            gradient[i] = start;

        return SUCCESS; // success
    }

    r = (fixp)start.r << FIXP_SHIFT;
    g = (fixp)start.g << FIXP_SHIFT;
    b = (fixp)start.b << FIXP_SHIFT;
    denominator = num_colors-1;
    half_denom = (denominator+1)>>1;
    delta_r = ((((fixp)end.r-start.r) << FIXP_SHIFT) + half_denom) / denominator;
    delta_g = ((((fixp)end.g-start.g) << FIXP_SHIFT) + half_denom) / denominator;
    delta_b = ((((fixp)end.b-start.b) << FIXP_SHIFT) + half_denom) / denominator;

    for (i = 0; i < num_colors; i++)
    {
        gradient[i].r = (r + FIXP_HALF) >> FIXP_SHIFT;
        gradient[i].g = (g + FIXP_HALF) >> FIXP_SHIFT;
        gradient[i].b = (b + FIXP_HALF) >> FIXP_SHIFT;
        r += delta_r;
        g += delta_g;
        b += delta_b;
    }

    return SUCCESS; // success
}
