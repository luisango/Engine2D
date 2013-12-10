#include "../include/particle.h"

void Particle::Update(double elapsed) {
    // double velocityx, velocityy;
    // double angularVelocity;
    // double lifetime;
    // double initialLifetime;
    // bool autofade;

    SetX(GetX() + velocityx * elapsed);
    SetY(GetY() + velocityy * elapsed);
}
