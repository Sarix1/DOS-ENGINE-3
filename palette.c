//#include <dos.h>
#include <conio.h>
#include "common.h"
#include "palette.h"
#include "vid_def.h"
#include "math_def.h"

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
        pal->colors[i].r = (pal->colors[i].r*scale) >> FIX_SHIFT;
        pal->colors[i].g = (pal->colors[i].g*scale) >> FIX_SHIFT;
        pal->colors[i].b = (pal->colors[i].b*scale) >> FIX_SHIFT;
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
    fixp scale = FIX_ONE;
    Palette_t pal;
    getVGAPalette(&pal);

    for (i = 0; i < 256; i++)
    {
        scale -= (FIX_ONE/256);
        for (j = 0; j < 256; j++)
        {
            setVGAPaletteColor_RGB(j,
            (pal.colors[j].r*scale) >> FIX_SHIFT,
            (pal.colors[j].g*scale) >> FIX_SHIFT,
            (pal.colors[j].b*scale) >> FIX_SHIFT);
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
        scale += (FIX_ONE/256);
        for (j = 0; j < 256; j++)
        {
            setVGAPaletteColor_RGB(j,
            (pal.colors[j].r*scale) >> FIX_SHIFT,
            (pal.colors[j].g*scale) >> FIX_SHIFT,
            (pal.colors[j].b*scale) >> FIX_SHIFT);
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