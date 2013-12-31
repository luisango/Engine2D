#ifndef UGINE_PIXELCOLLISION_H_
#define UGINE_PIXELCOLLISION_H_

#include "collision.h"
#include "../include/collisionmanager.h"

class PixelCollision : public Collision
{
public:
	PixelCollision(double* x, double* y, const CollisionPixelData* colPixelData) : x(x), y(y), colPixelData(colPixelData) {}
	
	virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(colPixelData, *x, *y); }
	virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToPixels(cx, cy, cradius, colPixelData, *x, *y); }
	virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().PixelsToRect(colPixelData, *x, *y, rx, ry, rwidth, rheight); }
	virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().PixelsToPixels(pixels, px, py, colPixelData, *x, *y); }
private:
	double* x;
	double* y;
	const CollisionPixelData* colPixelData;
};

#endif
