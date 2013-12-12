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

    Scene *scene = new Scene();

    Image *emission = rm.LoadImage("data/star.png");
    Emitter *emitter = scene->CreateEmitter(emission, true);
    

	Affector * affector = new Affector();
	affector->SetZone(0, 0, WIDTH, HEIGHT / 2);
	affector->SetMinColor(0, 0, 200);
	affector->SetMaxColor(0, 255, 255);
	affector->SetVelocityX(90, 100);
	affector->SetVelocityY(90, 100);


    emission->SetMidHandle();

    emitter->SetBlendMode(Renderer::BlendMode::ADDITIVE);
    emitter->SetRate(50, 100);
    emitter->SetVelocityX(-20, 20);
    emitter->SetVelocityY(-170, 0);
    emitter->SetAngularVelocity(0, 0);
    emitter->SetLifetime(1, 5);
    emitter->SetMinColor(150, 0, 0);
    emitter->SetMaxColor(255, 100, 50);
	emitter->AddAffector(affector);


	/*
    Array<Emitter *> emitters;
	int necessary_emitters = ceil((double) WIDTH * 2 / emission->GetWidth());

    for (int i = 0; i < necessary_emitters; i++)
    {
        emitters.Add(scene->CreateEmitter(emission, true));

		emitters.Last()->SetPosition(i * emission->GetWidth() / 2, HEIGHT);

        emitters.Last()->SetBlendMode(Renderer::BlendMode::ADDITIVE);
        emitters.Last()->SetRate(50, Random(70, 150));
        emitters.Last()->SetVelocityX(Random(-30, -10), Random(10, 30));
        emitters.Last()->SetVelocityY(Random(-250, -120), 10);
        emitters.Last()->SetAngularVelocity(0, 0);
        emitters.Last()->SetLifetime(1, Random(3, 7));
        emitters.Last()->SetMinColor(150, 0, 0);
        emitters.Last()->SetMaxColor(255, 100, 50);

		emitters.Last()->AddAffector(affector);
    }*/

	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{   
        renderer.Clear();
        // UPDATE EMISSION
        if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) 
            /*for (int i = 0; i < emitters.Size(); i++)
                emitters[i]->Start();*/
            emitter->Start();
        if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) 
            /*for (int i = 0; i < emitters.Size(); i++)
                emitters[i]->Stop();*/
            emitter->Stop();

        // UPDATE EMITTER POSITION
        emitter->SetX(screen.GetMouseX());
        emitter->SetY(screen.GetMouseY());

        // UPDATE SCENE
        scene->Update(screen.ElapsedTime());

        // RENDER SCENE
        scene->Render();

        // RENDER AIM
        renderer.SetBlendMode(Renderer::BlendMode::ADDITIVE);
        renderer.SetColor(255, 255, 255, 255);
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