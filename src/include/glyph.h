#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

#include "string.h"
#include "types.h" 
#include "image.h"

class Glyph
{ 
public:
	Glyph() { }
	Glyph(double bx, double by, double ex, double ey) : 
		begin_x(bx), begin_y(by), end_x(ex), end_y(ey) { }

	virtual void   SetBeginX(double bx) { this->begin_x = bx; }
	virtual double GetBeginX() { return begin_x; }
	virtual void   SetBeginY(double by) { this->begin_y = by; }
	virtual double GetBeginY() { return begin_x; }
	virtual void   SetEndX(double ex) { this->end_x = ex; }
	virtual double GetEndX() { return end_x; }
	virtual void   SetEndY(double ey) { this->end_y = ey; }
	virtual double GetEndY() { return end_x; }

private:
	double begin_x, begin_y;
	double end_x,   end_y;
};

#endif