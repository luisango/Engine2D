#include "../include/particle.h"

void Particle::Update(double elapsed) {
    SetX(GetX() + velocityx * elapsed);
    SetY(GetY() + velocityy * elapsed);
    
    if (lifetime <= 0)
        lifetime = 0;
    else 
        lifetime -= elapsed;

    SetAngle(GetAngle() + angularVelocity * elapsed);

    if (autofade)
        SetColor(
            GetRed(), 
            GetGreen(), 
            GetBlue(), 
            lifetime * 255 / initialLifetime
        );
}
/*
void Particle::Render(const Font * font) const 
{
    Sprite::Render();
    Renderer::Instance().DrawText(
        font,
        String::FromInt((int) GetGreen()) + " - " + String::FromInt((int) GetBlue()),
        GetX() + 5, GetY() + 5
    );
}*/
