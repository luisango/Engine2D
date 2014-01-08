#include "../include/isometricsprite.h"
#include "../include/image.h"
#include "../include/math.h"
#include <math.h>

void IsometricSprite::SetCollision(CollisionMode mode) {
    if (mode == Sprite::CollisionMode::COLLISION_PIXEL)
        mode = Sprite::CollisionMode::COLLISION_RECT;

    Sprite::SetCollision(mode);
}

void IsometricSprite::Update(double elapsed, const Map* map) {
    Sprite::Update(elapsed, map);

    TransformIsoCoords(GetX(), GetY(), GetZ(), &screenX, &screenY);
}

void IsometricSprite::UpdateCollisionBox() {
    double cx, cy, cw, ch;

    const Image * img = GetImage();

    cx = GetX() - img->GetHandleX() * fabs(GetScaleX());
	cy = GetY() - img->GetHandleX() * fabs(GetScaleX());
    cw = img->GetWidth() * fabs(GetScaleX());
	ch = img->GetWidth() * fabs(GetScaleX());

	Sprite::UpdateCollisionBox(cx, cy, cw, ch);
}
