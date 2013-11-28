#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
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
	lastFrame  = image->GetHFrames() * image->GetVFrames() - 1;
    currentFrame = 0;
	blendMode = Renderer::BlendMode::SOLID;
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
    delete image;
}

void Sprite::SetCollision(CollisionMode mode) {
	// TAREA: Implementar
}

bool Sprite::CheckCollision(Sprite* sprite) {
	// TAREA: Implementar
	return false;
}

bool Sprite::CheckCollision(const Map* map) {
	// TAREA: Implementar
	return false;
}

void Sprite::RotateTo(int32 angle, double speed) {
	// TAREA: Implementar
    toAngle = WrapValue(angle, 360);
    rotatingSpeed = speed;
    rotating = true;

    // METER LA LOGICA DE CUAL ESTÁ MAS CERCA
    //anguloDestino - anguloActual < anguloActual - anguloDestino
    int uno  = WrapValue(toAngle - this->angle, 360);
    int otro = WrapValue(this->angle - toAngle, 360);

    if ( uno > otro ) {
        anglesToRotate = otro;
    } else {
        rotatingSpeed *= -1;
        anglesToRotate = uno;
    }

    if (anglesToRotate > 200)
        int i = 0;
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	// TAREA: Implementar

	if (speedY == 0) {
		double time = Abs(this->x - x);
	}

    toX = x;
    toY = y;
    movingSpeedX = (toX < this->x) ? -1 * speedX : speedX;
    movingSpeedY = (toY < this->y) ? -1 * speedY : speedY;
    moving = true;
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion
    currentFrame += 1;
    
    if (currentFrame > lastFrame)
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
	if (moving) {
		x += movingSpeedX * elapsed;
		y += movingSpeedY * elapsed;

		if ( (movingSpeedX < 0 && x <= toX) || (0 < movingSpeedX && toX <= x) )
			x = toX;
		if ( (movingSpeedY < 0 && y <= toY) || (0 < movingSpeedY && toY <= y) )
			y = toY;

		if (x == toX && y == toY)
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

    Renderer::Instance().SetColor(255, 0, 255, 255);
    Renderer::Instance().DrawLine(
        GetX(),       GetY(), 
        GetX() + 200, GetY()
    );
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
