#ifndef UGINE_SPRITE_H
#define UGINE_SPRITE_H

#include "renderer.h"
#include "types.h"

class Collision;
class CollisionPixelData;
class Image;
class Map;

class Sprite {
public:
	enum CollisionMode {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_PIXEL,
		COLLISION_RECT
	};

	Sprite(Image* image);
	virtual ~Sprite();

    virtual void SetImage(Image* image) { this->image = image; }
    virtual const Image* GetImage() const { return image; }

    virtual void SetPosition(double x, double y, double z = 0) { SetX(x); SetY(y); SetZ(z); }
    virtual void SetX(double x) { this->x = x; }
    virtual void SetY(double y) { this->y = y; }
    virtual void SetZ(double z) { this->z = z; }
    virtual double GetX() const { return x; }
    virtual double GetY() const { return y; }
    virtual double GetZ() const { return z; }
    virtual double GetScreenX() const { return x; }
    virtual double GetScreenY() const { return y; }

	virtual void SetAngle(double angle) { this->angle = angle; }
    virtual double GetAngle() const { return angle; }

    virtual void SetScale(double sx, double sy) { SetScaleX(sx); SetScaleY(sy); }
    virtual void SetScaleX(double sx) { scalex = sx; }
    virtual void SetScaleY(double sy) { scaley = sy; }
    virtual double GetScaleX() const { return scalex; }
    virtual double GetScaleY() const { return scaley; }

	virtual void SetFPS(int16 fps) { animFPS = fps; }
	virtual int16 GetFPS() const { return animFPS; }
	virtual void SetFrameRange(uint16 firstFrame, uint16 lastFrame) { this->firstFrame = firstFrame; this->lastFrame = lastFrame; }
    virtual uint16 GetFirstFrame() const { return firstFrame; }
	virtual uint16 GetLastFrame() { return lastFrame; }
	virtual void SetCurrentFrame(uint16 frame) { currentFrame = frame; }
    virtual uint16 GetCurrentFrame() const { return currentFrame; }

	virtual void SetBlendMode(Renderer::BlendMode blend) { blendMode = blend; }
    virtual Renderer::BlendMode GetBlendMode() const { return blendMode; }
    virtual void SetColor(uint8 r, uint8 g, uint8 b, uint8 alpha = 255) { this->r = r; this->g = g; this->b = b; a = alpha; }
    virtual uint8 GetRed() const { return r; }
    virtual uint8 GetGreen() const { return g; }
    virtual uint8 GetBlue() const { return b; }
    virtual uint8 GetAlpha() const { return a; }

    virtual void SetRadius(double radius) { this->radius = radius; }
    virtual double GetRadius() const { return radius; }

	virtual void SetCollision(CollisionMode mode);
	virtual void SetCollisionPixelData(const CollisionPixelData* colPixelData) { this->colPixelData = colPixelData; }
    virtual const Collision* GetCollision() const { return collision; }
    virtual bool CheckCollision(Sprite* sprite);
    virtual bool CheckCollision(const Map* map);
	virtual const Sprite* CollisionSprite() const { return colSprite; }
	virtual bool DidCollide() const { return collided; }

    virtual void RotateTo(int32 angle, double speed);
    virtual void MoveTo(double x, double y, double speedX, double speedY = 0.0);
	virtual bool IsRotating() const { return rotating; }
	virtual bool IsMoving() const { return moving; }

    virtual void Update(double elapsed, const Map* map = NULL);
    virtual void Render() const;
protected:
    virtual void UpdateCollisionBox();
    virtual void UpdateCollisionBox(double x, double y, double w, double h);
private:
    Image* image;
    double x, y, z;
    double colx, coly, colwidth, colheight;
    double angle;
    double scalex, scaley;
    double radius;
    int16 animFPS;
    uint16 firstFrame, lastFrame;
    double currentFrame;
    Renderer::BlendMode blendMode;
    uint8 r, g, b, a;
    Collision* collision;
    const CollisionPixelData* colPixelData;
    Sprite* colSprite;
    bool collided;

    bool rotating;
    uint16 toAngle;
    double rotatingSpeed;
    double anglesToRotate;

    bool moving;
    double toX, toY;
    double movingSpeedX, movingSpeedY;
    double prevX, prevY;
};

#endif
