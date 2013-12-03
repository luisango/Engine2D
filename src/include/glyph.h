#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

#include "string.h"
#include "types.h" 
#include "image.h"

class Glyph
{ 
public:
	Glyph() { }
    Glyph(int frame_width, int frame_height, int glyph_row, int glyph_column, unsigned char * image_buffer);

    virtual double GetStartX() { return start_x; }
	virtual double GetStartY() { return start_y; }
	virtual double GetEndX() { return end_x; }
	virtual double GetEndY() { return end_y; }
    
    virtual double GetWidth() { return end_x - start_x; }
    virtual double GetHeight() { return end_y - start_y; }

private:
    virtual bool IsStartPixel(unsigned char r, unsigned char g, unsigned char b) { return r == 255 && g == 255 && b == 0; }
    virtual bool IsEndPixel(unsigned char r, unsigned char g, unsigned char b) { return r == 255 && g == 0 && b == 0; }

    virtual bool CanPixelBeSetToInvisible(unsigned char r, unsigned char g, unsigned char b) { return r == 0 && g == 0 && b == 0; }
    virtual void SetPixelToInvisible(unsigned char * r, unsigned char * g, unsigned char * b, unsigned char * a) { *r = *g = *b = *a = 0; }

private:
	double start_x, start_y;
	double end_x,   end_y;
};

#endif