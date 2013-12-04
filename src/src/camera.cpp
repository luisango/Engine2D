#include "../include/glinclude.h"
#include "../include/camera.h"
#include "../include/screen.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>

void Camera::Update()
{
    if (followingSprite) {
        double realx1 = boundx1 - Screen::Instance().GetWidth();
        double realy1 = boundy1 - Screen::Instance().GetHeight();

        // Update position
        x = followingSprite->GetX() - (Screen::Instance().GetWidth() / 2);
        y = followingSprite->GetY() - (Screen::Instance().GetHeight() / 2);

        // Check bounds
        if (x < boundx0) 
            x = boundx0;

        if (y < boundy0)
            y = boundy0;

        if (x > realx1)
            x = realx1;

        if (y > realy1)
            y = realy1;
    }
}
