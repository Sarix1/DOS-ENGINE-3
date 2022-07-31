#include <stdio.h>
#include <string.h>
#include "_malloc.h"
#include "_common.h"
#include "text_output.h"
#include "gfx_bitmap.h"
#include "gfx_video.h"
#include "gfx_draw_inline.h"

// Skip bytes in a file
void fskip(FILE* fp, int bytes)
{
    int i;
    for (i = 0; i < bytes; i++)
        fgetc(fp);
}

// Store a bitmap into a struct
void loadBitmap(Bitmap_t* b, char* filename, flags_t flags)
{
    FILE *fp;
    int num_colors;
    int32_t i, x;
    // Open the file
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Could not open file: %s.\n", filename);
        quit();
    }

    // Header
    // Ensure it is a valid bitmap file
    if (fgetc(fp) != 'B' || fgetc(fp) != 'M')
    {
        fclose(fp);
        fprintf(stderr, "Not a valid bitmap file: %s.\n", filename);
        quit();
    }
    // Get w, h, color count
    fskip(fp, 16);
    fread(&b->w, sizeof(uint16_t), 1, fp);
    fskip(fp, 2);
    fread(&b->h, sizeof(uint16_t), 1, fp);
    fskip(fp, 22);
    fread(&num_colors, sizeof(uint16_t), 1, fp);
    if (num_colors == 0)
        num_colors = 256;

    // Palette
    fskip(fp, 6);
    if (flags & LOAD_PALETTE)
    {
        for (i = 0; i < num_colors; i++)
        {
            // VGA palette RGB values have a 6-bit depth (0-63)
            // right shift out 2 bits, thus dividing the values by 4
            b->palette[i*3+2] = fgetc(fp) >> 2;
            b->palette[i*3+1] = fgetc(fp) >> 2;
            b->palette[i*3+0] = fgetc(fp) >> 2;
            fgetc(fp);
        }
    }
    else
        fskip(fp, num_colors*4);

    // Pixel data;
    if (flags & LOAD_IMAGE)
    {
        // Allocate memory for bitmap data
        b->data = (byte*)malloc(b->w * b->h);
        if (b->data == NULL)
        {
            fclose(fp);
            // change this to use 
            fprintf(stderr, "Failed to allocate memory for bitmap file: %s.\n", filename);
            quit();//(g_String);
        }
        // Load bitmap data
        for (i = (b->h-1) * b->w; i >= 0; i -= b->w)
            for (x = 0; x < b->w; x++)
                b->data[i+x] = fgetc(fp);
    }
    fclose(fp);
}

void freeBitmap(Bitmap_t* bmp)
{
    free(bmp->data);
    free(bmp);
}

// Copy a bitmap to the screen buffer
void drawBitmap(Bitmap_t* bmp, int x, int y)
{
    int row;
    byte* image_offset = bmp->data;
    byte far* screen_offset = g_Video.surface + Y_OFFSET(y) + x;
    
    for (row = 0; row < bmp->h; row++)
    {
        memcpy(screen_offset, image_offset, bmp->w);
        image_offset += bmp->w;
        screen_offset += SCREEN_WIDTH;
    }
}

// Convert a bitmap of 256 8x8 characters into a C byte array
void convertFont8x8(char* bmp_filename, char* output_filename)
{
    FILE* fp;
    Bitmap_t bmp_font;
    byte charset[256][8];
    int i, j, k, x, y, bit;

    loadBitmap(&bmp_font, bmp_filename, 0);
    g_Video.surface = g_Video.screen;
    drawBitmap(&bmp_font, 0, 0);
    //renderVideo();

    x = 0;
    y = 0;
    for (i = 0; i < 256; i++)
    {
        for (j = 0; j < 8; j++)
        {
            charset[i][j] = 0x00;
            for (k = 0; k < 8; k++)
            {
                if (getPixel(x+k, y+j) != 0)
                    charset[i][j] |= 1 << k;
            }
        }

        x += 8;
        if (x >= bmp_font.w)
        {
            x = 0;
            y += 8;
        }
    }

    delay(1000);

    fp = fopen(output_filename, "w");
    fprintf(fp, "const unsigned char charset_8x8[256][8] =\n{\n");

    for (i = 0; i < 256; i++)
    {
        fprintf(fp, "    { ");
        for (j = 0; j < 7; j++)
            fprintf(fp, "0x%02x, ", charset[i][j]);
        fprintf(fp, "0x%02x }", charset[i][j]);
        if (i < 255)
            fputc(',', fp);
        if (i < 32)
            fprintf(fp, " // code %d\n", i);
        else
            fprintf(fp, " // %c\n", i);
    }

    fprintf(fp, "};\n");
    fclose(fp);
    freeBitmap(&bmp_font);
    
    exit();
}
