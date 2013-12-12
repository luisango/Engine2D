#ifndef UGINE_EMITTER_H
#define UGINE_EMITTER_H

#include "array.h"
#include "particle.h"
#include "renderer.h"
#include "types.h"
#include "resourcemanager.h"
#include "affector.h"

class Image;

class Emitter {
public:
    Emitter(Image* image, bool autofade) { this->image = image; this->autofade = autofade; this->blendMode = Renderer::ALPHA; SetPosition(0, 0); SetRate(1, 10); SetVelocityX(0, 0); SetVelocityY(0, 0); SetAngularVelocity(0, 0); SetLifetime(1, 5); SetMinColor(0, 0, 0); SetMaxColor(255, 255, 255); Stop(); /*this->debug_font = ResourceManager::Instance().LoadFont("data/monospaced.png");*/}

    virtual void SetPosition(double x, double y) { SetX(x); SetY(y); }
    virtual void SetX(double x) { this->x = x; }
    virtual void SetY(double y) { this->y = y; }
    virtual double GetX() const { return x; }
    virtual double GetY() const { return y; }

    virtual void SetRate(double minrate, double maxrate) { this->minrate = minrate; this->maxrate = maxrate; }
    virtual void SetVelocityX(double minvelx, double maxvelx) { this->minvelx = minvelx; this->maxvelx = maxvelx; }
    virtual void SetVelocityY(double minvely, double maxvely) { this->minvely = minvely; this->maxvely = maxvely; }
    virtual void SetAngularVelocity(double minangvel, double maxangvel) { this->minangvel = minangvel; this->maxangvel = maxangvel; }
    virtual void SetLifetime(double minlifetime, double maxlifetime) { this->minlifetime = minlifetime; this->maxlifetime = maxlifetime; }
    virtual void SetMinColor(uint8 r, uint8 g, uint8 b) { minr = r; ming = g; minb = b; }
    virtual void SetMaxColor(uint8 r, uint8 g, uint8 b) { maxr = r; maxg = g; maxb = b; }
    virtual void SetBlendMode(Renderer::BlendMode mode) { blendMode = mode; }

    virtual void Start() { emitting = true; }
    virtual void Stop() { emitting = false; }
    virtual bool IsEmitting() const { return emitting; }

    virtual void Update(double elapsed);
    virtual void Render() const;

	virtual void AddAffector(Affector * a) { affectors.Add(a); }

private:
    Image* image;
    bool autofade;
    double x, y;

    double minrate, maxrate;
    double minvelx, maxvelx;
    double minvely, maxvely;
    double minangvel, maxangvel;
    double minlifetime, maxlifetime;
    uint8 minr, ming, minb;
    uint8 maxr, maxg, maxb;
    Renderer::BlendMode blendMode;

    bool emitting;
    Array<Particle> particles;
	Array<Affector *> affectors;

    //const Font * debug_font;
};

#endif
