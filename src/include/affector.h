#ifndef UGINE_AFFECTOR_H
#define UGINE_AFFECTOR_H

#include "emitter.h"
#include "particle.h"

class Affector 
{
public:
	Affector() { }

	virtual void SetZone(double x0, double y0, double x1, double y1) { this->x0 = x0; this->x1 = x1; this->y0 = y0; this->y1 = y1; }
	virtual void SetVelocityX(double minvelx, double maxvelx) { this->minvelx = minvelx; this->maxvelx = maxvelx; }
    virtual void SetVelocityY(double minvely, double maxvely) { this->minvely = minvely; this->maxvely = maxvely; }
    virtual void SetAngularVelocity(double minangvel, double maxangvel) { this->minangvel = minangvel; this->maxangvel = maxangvel; }
    virtual void SetMinColor(uint8 r, uint8 g, uint8 b) { minr = r; ming = g; minb = b; }
    virtual void SetMaxColor(uint8 r, uint8 g, uint8 b) { maxr = r; maxg = g; maxb = b; }

	// START TIENE QUE SER MENOR QUE END!!!!!!
	virtual double GetStartX() { return x0; }
	virtual double GetStartY() { return y0; }
	virtual double GetEndX() { return x1; }
	virtual double GetEndY() { return y1; }

	virtual bool IsParticleAffected(Particle * p);
	virtual void AffectParticle(Particle * p);
	virtual void RemoveParticle(Particle * p);

private:
	double x0, x1, y0, y1;
	uint8 minr, maxr, ming, maxg, minb, maxb;
	int minvelx, maxvelx, minvely, maxvely;
	int minangvel, maxangvel;

	Array<Particle *> affected_particles;
};

#endif