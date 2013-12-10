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

    Scene *scene = new Scene();

    Image *emission = rm.LoadImage("data/star.png");
    Emitter *emitter = scene->CreateEmitter(emission, true);
    
    emission->SetMidHandle();

    emitter->SetRate(500, 1000);
    emitter->SetVelocityX(-128, 128);
    emitter->SetVelocityY(-128, 128);
    emitter->SetAngularVelocity(0, 360);
    emitter->SetLifetime(1, 2);
    emitter->SetMinColor(0, 0, 0);
    emitter->SetMaxColor(255, 255, 255);

	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{   
        renderer.Clear();
        // UPDATE EMISSION
        if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) 
            emitter->Start();
        else 
            emitter->Stop();

        // UPDATE EMITTER POSITION
        emitter->SetX(screen.GetMouseX());
        emitter->SetY(screen.GetMouseY());

        // UPDATE SCENE
        scene->Update(screen.ElapsedTime());

        // RENDER SCENE
        scene->Render();

        // RENDER AIM
        renderer.SetBlendMode(Renderer::BlendMode::ALPHA);
        renderer.DrawImage(
            emission,
            screen.GetMouseX(), screen.GetMouseY(),
            0,
            emission->GetWidth(), emission->GetHeight()
        );

        // Refrescamos la pantalla 
        screen.Refresh();
    } 

	rm.FreeResources();

    return 0; 
}