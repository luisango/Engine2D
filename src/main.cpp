#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const bool FULLSCREEN = false;

int main(int argc, char* argv[])
{ 
    Screen& screen           = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();
    ResourceManager& rm      = ResourceManager::Instance(); 

    screen.Open(WIDTH, HEIGHT, FULLSCREEN); 
    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetMousePos(WIDTH / 2, HEIGHT / 2);

    Scene* scene = new Scene();

    // Load images
	Image* img_ball         = rm.LoadImage("data/ball.png");
    Image* img_box          = rm.LoadImage("data/box.jpg");
    Image* img_alien        = rm.LoadImage("data/alien.png");
    Image* img_mouse_circle = rm.LoadImage("data/circle.png");
    Image* img_mouse_rect   = rm.LoadImage("data/rect.png");

    // Mid handles
	img_ball->SetMidHandle();
    img_box->SetMidHandle();
    img_alien->SetMidHandle();
    img_mouse_circle->SetMidHandle();
    img_mouse_rect->SetMidHandle();

    // Create sprites
    Sprite* spr_ball  = scene->CreateSprite(img_ball);
    Sprite* spr_box   = scene->CreateSprite(img_box);
    Sprite* spr_alien = scene->CreateSprite(img_alien);
    Sprite* spr_mouse = scene->CreateSprite(img_mouse_circle); // Circle by default 

    // Set sprites' properties
    spr_ball->SetPosition(WIDTH * 1/4, HEIGHT * 1/4);
    spr_ball->SetRadius(img_ball->GetWidth() / 2 - 4);
    spr_ball->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);

    spr_box->SetPosition(WIDTH * 3/4, HEIGHT * 3/4);
    spr_box->SetCollision(Sprite::CollisionMode::COLLISION_RECT);

    CollisionPixelData* col_alien = rm.LoadCollisionPixelData("data/aliencol.png");
	spr_alien->SetCollisionPixelData(col_alien);
    spr_alien->SetPosition(img_alien->GetWidth()/2, img_alien->GetHeight()/2);//WIDTH * 1/4, HEIGHT * 3/4);
	spr_alien->SetCollision(Sprite::CollisionMode::COLLISION_PIXEL);

    // Set mouse properties
    glfwSetMousePos(WIDTH / 2, HEIGHT / 2);
	//glfwDisable(GLFW_MOUSE_CURSOR);

	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{   
        renderer.Clear();
        
        // Update scene
        scene->Update(screen.ElapsedTime());

        // Update mouse
        spr_mouse->SetPosition(screen.GetMouseX(), screen.GetMouseY());

        // Update mouse sprite
        if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || !spr_mouse->GetCollision()) {
            spr_mouse->SetImage(img_mouse_circle);
            spr_mouse->SetRadius(img_mouse_circle->GetWidth() / 2);
            spr_mouse->SetCollision(Sprite::CollisionMode::COLLISION_CIRCLE);
        } else if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
            spr_mouse->SetImage(img_mouse_rect);
            spr_mouse->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
        } else if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
            spr_mouse->SetImage(img_alien);
            spr_mouse->SetCollisionPixelData(col_alien);
            spr_mouse->SetCollision(Sprite::CollisionMode::COLLISION_PIXEL);
        }

        // Update collision tint for mouse
        if (spr_mouse->DidCollide()) {
			spr_mouse->SetColor(0, 255, 0, 100);
            spr_mouse->SetBlendMode(Renderer::BlendMode::ADDITIVE);
        } else {
			spr_mouse->SetColor(255, 255, 255);
            spr_mouse->SetBlendMode(Renderer::BlendMode::ALPHA);
        }

        // Update collision tint for box
		if (spr_box->DidCollide()) {
			spr_box->SetColor(255, 255, 0);
		} else {
			spr_box->SetColor(255, 255, 255);
        }

		if (spr_ball->DidCollide()) {
			spr_ball->SetColor(255, 255, 0);
		} else {
			spr_ball->SetColor(255, 255, 255);
        }
        
		if (spr_alien->DidCollide()) {
			spr_alien->SetColor(255, 255, 0);
		} else {
			spr_alien->SetColor(255, 255, 255);
        }

        
        // Draw
        scene->Render();

        // Refrescamos la pantalla 
        screen.Refresh();
    } 

	rm.FreeResources();

    return 0; 
}