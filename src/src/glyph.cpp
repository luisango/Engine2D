#include "../include/glyph.h"
#include <math.h>
#include <stdlib.h>

Glyph::Glyph(int frame_width, int frame_height, int glyph_row, int glyph_column, unsigned char * image_buffer)
{
    unsigned char *r, *g, *b, *a;

    int start_x = glyph_column * frame_width;
    int start_y = glyph_row * frame_height;

    this->start_x = start_x;
    this->start_y = start_y;

    int end_x = GetStartX() + frame_width  - 1;
    int end_y = GetStartY() + frame_height - 1;

    this->end_x = end_x;
    this->end_y = end_y;

    for (int y = start_y; y <= end_y; y++)
        for (int x = start_x; x <= end_x; x ++) // (y * width + x) * 4
        {
			int p = (y * frame_width * 16 + x) * 4;

            r = &image_buffer[p];
            g = &image_buffer[p + 1];
            b = &image_buffer[p + 2];
            a = &image_buffer[p + 3];

            if (IsStartPixel(*r, *g, *b)) 
            {
                this->start_x = x;
                this->start_y = y;

                SetPixelToInvisible(r, g, b, a);
            } 
            else if (IsEndPixel(*r, *g, *b)) 
            {
                this->end_x = x;
                this->end_y = y;

                SetPixelToInvisible(r, g, b, a);
            }
            else if (CanPixelBeSetToInvisible(*r, *g, *b)) 
            {
                SetPixelToInvisible(r, g, b, a);
            }
        }
}