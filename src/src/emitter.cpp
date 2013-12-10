#include "../include/emitter.h"
#include "../include/math.h"
#include <stdlib.h>

void Emitter::Update(double elapsed) {
    // bool autofade;
    // double x, y;
       
    // double minrate, maxrate;
    // double minvelx, maxvelx;
    // double minvely, maxvely;
    // double minangvel, maxangvel;
    // double minlifetime, maxlifetime;
    // uint8 minr, ming, minb;
    // uint8 maxr, maxg, maxb;
    // Renderer::BlendMode blendMode;
       
    // bool emitting;
    // Array<Particle> particles;

    if (emitting) {
        int rate = 0, r = 0, g = 0, b = 0;
        double xvel = 0, yvel = 0, avel = 0, life = 0;

        rate = Random(minrate, maxrate);

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
            p.SetX(x);
            p.SetY(y);
            p.SetColor(r, g, b);

            particles.Add(p);
        }
    }

    // Update particles
    for (int i = 0; particles.Size(); i++)
    {
        particles[i].Update(elapsed);
    }
}

void Emitter::Render() const {
    for (int i = 0; particles.Size(); i++)
    {
        particles[i].Render();
    }
}
