#include "../include/sprite.h"
#include "../include/screen.h"
#include "../include/rectcollision.h"
#include "../include/image.h"
#include "../include/map.h"
#include "../include/math.h"
#include "../include/pixelcollision.h"
#include "../include/renderer.h"
#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(Image* image) {
	this->image = image;
    x = y = z = 0;
    colx = coly = colwidth = colheight = 0;
    angle = 0;
    scalex = scaley = 1;
    radius = 0;
    animFPS = 30;
    firstFrame = 0;
	lastFrame  = (image != NULL) ? image->GetNumFrames() - 1 : 0;
    currentFrame = 0;
	blendMode = Renderer::BlendMode::ALPHA;
    r = g = b = a = 255;
    collision = NULL;
    colPixelData = NULL;
    colSprite = NULL;
    collided = false;

    rotating = false;
    toAngle = 0;
    rotatingSpeed = 0;
    anglesToRotate = 0;

    moving = false;
    toX = toY = 0;
    movingSpeedX = movingSpeedY = 0;
    prevX = prevY = 0;
}

Sprite::~Sprite() {
    image = NULL;
}

void Sprite::SetCollision(CollisionMode mode) {
	if (collision)
        delete collision;

    switch (mode)
    {
    case COLLISION_NONE:
        collision = NULL;
        break;
    case COLLISION_CIRCLE:
        collision = new CircleCollision(&x, &y, &radius);
		break;
	case COLLISION_PIXEL:
		collision = new PixelCollision(&colx, &coly, colPixelData);
		break;
	case COLLISION_RECT:
		collision = new RectCollision(&colx, &coly, &colwidth, &colheight);
		break;
    }
}

bool Sprite::CheckCollision(Sprite* sprite) {
	if (collision && sprite->GetCollision())
		if (collision->DoesCollide(sprite->GetCollision()))
		{
			colSprite         = sprite;
			collided          = true;
			sprite->colSprite = this;
			sprite->collided  = true;
			return true;
		}

	return false;
}

bool Sprite::CheckCollision(const Map* map) {
	// TAREA: Implementar

    if (collision  &&  map->CheckCollision(collision)) {
		collided = true;
		return true;
	}
		return false;
}

void Sprite::RotateTo(int32 angle, double speed) {
	// TAREA: Implementar
    toAngle = WrapValue(angle, 360);
    rotatingSpeed = speed;
    rotating = true;

    // METER LA LOGICA DE CUAL ESTÁ MAS CERCA
    int uno  = WrapValue(toAngle - this->angle, 360);
    int otro = WrapValue(this->angle - toAngle, 360);

    if ( uno > otro ) {
        anglesToRotate = otro;
    } else {
        rotatingSpeed *= -1;
        anglesToRotate = uno;
    }
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	// TAREA: Implementar
    

    toX = x;
    toY = y;
    moving = true;

	if (speedY == 0) {
		double time = Abs((toX - this->x) / speedX) + Abs((toY - this->y) / speedX);
         
        movingSpeedX = Abs(toX - this->x) / time;
        movingSpeedY = Abs(toY - this->y) / time;
	} else {
        movingSpeedX = speedX;
        movingSpeedY = speedY;
    }
    
    movingSpeedX = (toX < this->x) ? -1 * Abs(movingSpeedX) : Abs(movingSpeedX);
    movingSpeedY = (toY < this->y) ? -1 * Abs(movingSpeedY) : Abs(movingSpeedY);
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion

    // Actualizamos la animación 
    currentFrame += animFPS * elapsed;

    // Si nos intentan trolear con frames que no existen...
	if (currentFrame < firstFrame)
		currentFrame = firstFrame;

    // Si se pasa del ultimo frame... (y en caso de que *elapsed)
	if (currentFrame >= lastFrame + 1)
		currentFrame = firstFrame;

	// TAREA: Actualizar rotacion animada
    if (rotating) {
        anglesToRotate -= Abs(rotatingSpeed) * elapsed;
        angle -= rotatingSpeed * elapsed;
        angle = WrapValue(angle, 360);
        
        if (anglesToRotate <= 0) {
            angle = toAngle;
            rotating = false;
        }
    }
    
	// TAREA: Actualizar movimiento animado
	if (moving)
	{
		prevX = x;
		prevY = y;

		x = x + movingSpeedX * elapsed;
		y = y + movingSpeedY * elapsed;

		UpdateCollisionBox();
		if (map && CheckCollision(map))
		{
			x = prevX;
			y = prevY;
		}
		
		if ((movingSpeedX < 0 && x <= toX) || (0 < movingSpeedX && toX <= x))
			x = toX;
		if ((movingSpeedY < 0 && y <= toY) || (0 < movingSpeedY && toY <= y))
			y = toY;

		if ((x == prevX && y == prevY) || (x == toX && y == toY))
			moving = false;
	}

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
    Renderer::Instance().SetBlendMode(blendMode);
    Renderer::Instance().SetColor(r, g, b, a);
    Renderer::Instance().DrawImage(
		GetImage(), 
        GetX(), GetY(), 
		GetCurrentFrame(), 
		GetImage()->GetWidth()  * GetScaleX(), 
		GetImage()->GetHeight() * GetScaleY(), 
		GetAngle()
	);
}

void Sprite::UpdateCollisionBox() {
	double cx, cy, cw, ch;

	cx = x - image->GetHandleX() * fabs(scalex);
	cy = y - image->GetHandleY() * fabs(scaley);
	cw = image->GetWidth() * fabs(scalex);
	ch = image->GetHeight() * fabs(scaley);

	UpdateCollisionBox(cx, cy, cw, ch);
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
    colx = x;
	coly = y;
	colwidth = w;
	colheight = h;
}