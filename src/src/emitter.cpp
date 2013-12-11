#include "../include/emitter.h"
#include "../include/math.h"
#include <stdlib.h>

void Emitter::Update(double elapsed) {

	// Array de borrado de particulas
	Array<uint32> particlesToDelete;

    if (emitting) {
        unsigned int rate = 0, r = 0, g = 0, b = 0;
        double xvel = 0, yvel = 0, avel = 0, life = 0;

        rate = (unsigned int) Random(minrate, maxrate) * elapsed;

        for (int i = 0; i < rate; i++)
        {
            xvel = Random(minvelx, maxvelx);
            yvel = Random(minvely, maxvely);
            avel = Random(minangvel, maxangvel);
            life = Random(minlifetime, maxlifetime);

            r = Random(minr, maxr);
            g = Random(ming, maxg);
            b = Random(minb, maxb);

            Particle p(image, xvel, yvel, avel, life, autofade);
            p.SetPosition(x, y);
            p.SetColor(r, g, b, 255);
			p.SetBlendMode(blendMode);
            
            particles.Add(p);
        }
    }

    // Update particles
    for (int i = 0; i < particles.Size(); i++)
    {
        particles[i].Update(elapsed);

		if (particles[i].GetLifetime() <= 0)
			particlesToDelete.Add(i);
    }

	// Delete dead particles
	for (int i = particlesToDelete.Size() - 1; i > 0; i--)
	{
        particles.RemoveAt(particlesToDelete[i]);
    }
}

void Emitter::Render() const {
    for (int i = 0; i < particles.Size(); i++)
    {
        particles[i].Render();
    }
}
