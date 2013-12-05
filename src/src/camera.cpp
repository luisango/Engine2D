#include "../include/glinclude.h"
#include "../include/camera.h"
#include "../include/screen.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>

void Camera::SetX(double x)
{
    double realx1 = boundx1 - Screen::Instance().GetWidth();

	if (x < boundx0)
		this->x = boundx0;
	else if (x > realx1)
		this->x = realx1;
	else
		this->x = x;
}

void Camera::SetY(double y)
{
    double realy1 = boundy1 - Screen::Instance().GetHeight();

	if (y < boundy0)
		this->y = boundy0;
	else if (y > realy1)
		this->y = realy1;
	else
		this->y = y;
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1)
{
	boundx0 = bx0; 
	boundx1 = bx1; 
	boundy0 = by0; 
	boundy1 = by1;

	if (boundx0 > boundx1)
		boundx1 = boundx0;
	if (boundy0 > boundy1)
		boundy1 = boundy0;
}

void Camera::Update()
{
    if (followingSprite) {
        // Update position
        x = followingSprite->GetX() - (Screen::Instance().GetWidth() / 2);
        y = followingSprite->GetY() - (Screen::Instance().GetHeight() / 2);
	}
    
	// Check bounds
	SetPosition(x, y);
}
