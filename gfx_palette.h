#ifndef PALETTE_H
#define PALETTE_H

#include "gfx_palette_structs.h"

/* function prototypes */

void    setVGAPalette           (Palette_t* pal);
void    getVGAPalette           (Palette_t* pal);
void    setVGAPaletteColor_RGB  (byte index, byte red, byte green, byte blue);
void    setVGAPaletteColor      (byte index, Color_t color);
Color_t getPaletteColor_VGA     (byte index);
void    setPaletteColor_RGB     (Palette_t* pal, byte index, byte r, byte g, byte b);
void    setPaletteColor         (Palette_t* pal, byte index, Color_t color);
Color_t getPaletteColor         (Palette_t* pal, byte index);
void    scalePalette            (Palette_t* pal, fixp scale);
void    setWholePalette         (Palette_t* pal, byte r, byte g, byte b);
void    fadeToBlack             ();
void    fadeFromBlack           ();
void    rotatePaletteLeft       (Palette_t* pal);
void    rotatePaletteRight      (Palette_t* pal);
void    rotatePaletteLeftBy     (Palette_t* pal, const unsigned n_first, const unsigned first, const unsigned stop);
void    rotatePalette           (Palette_t* pal, const int n,            const unsigned first, const unsigned end);

#endif/* PALETTE_H */
