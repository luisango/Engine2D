#ifndef UGINE_PARTICLE_H
#define UGINE_PARTICLE_H

#include "sprite.h"

class Particle : public Sprite {
public:
    Particle() 
        : Sprite(NULL), velocityx(0), velocityy(0), angularVelocity(0), lifetime(0), initialLifetime(0), autofade(false) { SetBlendMode(Renderer::ALPHA); }

	Particle(Image* image, double velocityx, double velocityy, double angularVelocity, double lifetime, bool autofade)
        : Sprite(image), velocityx(velocityx), velocityy(velocityy), angularVelocity(angularVelocity), lifetime(lifetime), initialLifetime(lifetime), autofade(autofade) { SetBlendMode(Renderer::ALPHA); }

    virtual double GetLifetime() const { return lifetime; }
    
	virtual void Update(double elapsed);

    //virtual void Render(const Font * font) const;
private:
    double velocityx, velocityy;
    double angularVelocity;
    double lifetime;
    double initialLifetime;
    bool autofade;
};

#endif
