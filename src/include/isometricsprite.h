#ifndef UGINE_ISOMETRICSPRITE_H
#define UGINE_ISOMETRICSPRITE_H

#include "sprite.h"

class IsometricSprite : public Sprite {
public:
    IsometricSprite(Image* image)  : Sprite(image), screenX(0), screenY(0) {}

    virtual double GetScreenX() const { return screenX; }
    virtual double GetScreenY() const { return screenY; }

    virtual void SetCollision(CollisionMode mode);

    virtual void Update(double elapsed, const Map* map = NULL);
protected:
    virtual void UpdateCollisionBox();
private:
    double screenX, screenY;
};

#endif
