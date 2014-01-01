#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const bool FULLSCREEN = false;
const int SPEED = 500;

int main(int argc, char* argv[])
{ 
    Screen& screen           = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();
    ResourceManager& rm      = ResourceManager::Instance(); 

    screen.Open(WIDTH, HEIGHT, FULLSCREEN); 
    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetMousePos(WIDTH / 2, HEIGHT / 2);

    Map* map = rm.LoadMap("data/map.tmx");

    Image* img_alien   = rm.LoadImage("data/alien.png");
    Image* img_front   = rm.LoadImage("data/frontlayer.png");
    Image* img_back    = rm.LoadImage("data/backlayer.png");
    Image* img_emitter = rm.LoadImage("data/star.png");

    MapScene* scene = new MapScene(map, img_back, img_front);
    scene->SetRelativeBackSpeed(0.5, 0.5);
    scene->SetRelativeFrontSpeed(1.3, 1.3);
    scene->SetAutoBackSpeed(-58, 58);
    scene->SetAutoFrontSpeed(50, -50);

    Emitter* emt_alien = scene->CreateEmitter(img_emitter, true);
    emt_alien->SetLifetime(3, 5);
    emt_alien->SetMinColor(0, 0, 0);
    emt_alien->SetMaxColor(255, 255, 255);
    emt_alien->SetRate(61, 100);

    Sprite * spr_alien = scene->CreateSprite(img_alien);
    spr_alien->SetPosition(192, 400);
    spr_alien->SetCollision(Sprite::COLLISION_RECT);

    Camera& cam = scene->GetCamera();
    cam.SetBounds(0, 0, scene->GetMap()->GetWidth(), scene->GetMap()->GetHeight());
    scene->GetCamera().FollowSprite(spr_alien);

    spr_alien->SetX(WIDTH / 2);
    spr_alien->SetY(HEIGHT / 2);

	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{   
        renderer.Clear();
        
        // Update sprite
        if (screen.KeyPressed(GLFW_KEY_LEFT))
            spr_alien->SetX(spr_alien->GetX() - (SPEED * screen.ElapsedTime()));
        if (screen.KeyPressed(GLFW_KEY_RIGHT))
            spr_alien->SetX(spr_alien->GetX() + (SPEED * screen.ElapsedTime()));
        if (screen.KeyPressed(GLFW_KEY_UP)) 
            spr_alien->SetY(spr_alien->GetY() - (SPEED * screen.ElapsedTime()));
        if (screen.KeyPressed(GLFW_KEY_DOWN)) 
            spr_alien->SetY(spr_alien->GetY() + (SPEED * screen.ElapsedTime()));

        // Update emitter
        emt_alien->SetPosition(
            spr_alien->GetX(),
            spr_alien->GetY()
        );

        // Collision
        if (spr_alien->DidCollide())
            emt_alien->Start();

        // Update scene
        scene->Update(screen.ElapsedTime());

        // Draw scene
        scene->Render();

        // Refrescamos la pantalla 
        screen.Refresh();
    } 

	rm.FreeResources();

    return 0; 
}