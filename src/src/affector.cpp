#include "../include/affector.h"
#include "../include/math.h"
#include <stdlib.h>

bool Affector::IsParticleAffected(Particle * p)
{
	for (int i = 0; i < affected_particles.Size(); i++)
	{
		if (p == affected_particles[i])
			return true;
	}

	return false;
}

void Affector::AffectParticle(Particle * p)
{
	p->velocityx = Random(minvelx, maxvelx);
	p->velocityy = Random(minvely, maxvely);

	p->angularVelocity = Random(minangvel, maxangvel);

	p->SetColor(
		Random(minr, maxr),
		Random(ming, maxg),
		Random(minb, maxb),
		p->GetAlpha()
	);

	affected_particles.Add(p);
}

void Affector::RemoveParticle(Particle * p)
{
	for (int i = 0; i < affected_particles.Size(); i++)
	{
		if (p == affected_particles[i]) {
			affected_particles.Remove(p);
			return;
		}
	}
}