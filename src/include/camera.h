#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H

#include "types.h"
#include "sprite.h"

class Camera 
{
public:
    Camera() : x(0), y(0), boundx0(0), boundx1(0), boundy0(0), boundy1(0), followingSprite(0) { }

    virtual void SetPosition(double x, double y) { SetX(x); SetY(y); }

	virtual void SetX(double x);
	virtual void SetY(double y);

	virtual double GetX() const { return x; }
	virtual double GetY() const { return y; }

    virtual void SetBounds(double bx0, double by0, double bx1, double by1);
    virtual bool HasBounds() const { return boundx1 != boundx0; }

    virtual double GetMinX() const { return boundx0; }
    virtual double GetMinY() const { return boundx1; }

    virtual double GetMaxX() const { return boundy0; }
    virtual double GetMaxY() const { return boundy1; }

    virtual void FollowSprite(Sprite* sprite) { followingSprite = sprite; }

	virtual void Update();

private:
	double x, y;
	double boundx0, boundy0, boundx1, boundy1;
	Sprite* followingSprite;
};

#endif