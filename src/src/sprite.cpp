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
    colx, coly, colwidth, colheight = 0;
    angle = 0;
    scalex, scaley = 1;
    radius = 0;
    animFPS = 30;
    firstFrame = 0;
	lastFrame  = image->GetHFrames() * image->GetVFrames() - 1;
    currentFrame = 0;
	blendMode = Renderer::BlendMode::SOLID;
    r, g, b, a = 255;
    collision = NULL;
    colPixelData = NULL;
    colSprite = NULL;
    collided = false;

    rotating = false;
    toAngle = 0;
    rotatingSpeed = 0;
    anglesToRotate = 0;

    moving = false;
    toX, toY = 0;
    movingSpeedX, movingSpeedY = 0;
    prevX, prevY = 0;
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
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	// TAREA: Implementar
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion

	// TAREA: Actualizar rotacion animada

	// TAREA: Actualizar movimiento animado

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
    // TAREA: Implementar
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
