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

    Image *emission = rm.LoadImage("data/light.png");
    emission->SetMidHandle();

    Emitter *emitter = scene->CreateEmitter(emission, true);

	Affector * affector = new Affector();
	affector->SetZone(0, 0, WIDTH, HEIGHT / 2);
    affector->SetAngularVelocity(30, 130);
	affector->SetMinColor(100, 100, 100);
	affector->SetMaxColor(100, 100, 100);
	affector->SetVelocityX(-100, 100);
	affector->SetVelocityY(-190, -100);

    Affector * affector2 = new Affector();
	affector2->SetZone(WIDTH / 3, HEIGHT / 3, WIDTH * 2 / 3, HEIGHT * 2 / 3 );
    affector2->SetAngularVelocity(30, 130);
	affector2->SetMinColor(0, 0, 100);
	affector2->SetMaxColor(0, 100, 255);
	affector2->SetVelocityX(-100, 100);
	affector2->SetVelocityY(-100, 0);

    emitter->SetBlendMode(Renderer::BlendMode::ADDITIVE);
    emitter->SetRate(50, 100);
    emitter->SetVelocityX(-20, 20);
    emitter->SetVelocityY(-170, 0);
    emitter->SetAngularVelocity(0, 0);
    emitter->SetLifetime(1, 5);
    emitter->SetMinColor(150, 0, 0);
    emitter->SetMaxColor(255, 100, 50);
	emitter->AddAffector(affector);
    emitter->AddAffector(affector2);
	
    Array<Emitter *> emitters;
	int necessary_emitters = ceil((double) WIDTH * 2 / emission->GetWidth()) + 1;

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
        emitters.Last()->AddAffector(affector2);
    }

	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{   
        renderer.Clear();
        // UPDATE EMISSION
        if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            for (int i = 0; i < emitters.Size(); i++)
                emitters[i]->Start();
            emitter->Start();
        }

        if (screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
            for (int i = 0; i < emitters.Size(); i++)
                emitters[i]->Stop();
            emitter->Stop();
        }

        // UPDATE EMITTER POSITION
        emitter->SetX(screen.GetMouseX());
        emitter->SetY(screen.GetMouseY());

        // UPDATE SCENE
        scene->Update(screen.ElapsedTime());

        // RENDER SCENE
        scene->Render();
//        screen.SetTitle("E = " + String::FromInt(emitter->GetTotalParticles()) + " / A = " + String::FromInt(emitter->GetAffectors()[0]->GetTotalParticles()));
        // RENDER AIM
        renderer.SetBlendMode(Renderer::BlendMode::ADDITIVE);
        renderer.SetColor(255, 255, 255, 255);
        renderer.DrawImage(
            emission,
            screen.GetMouseX(), screen.GetMouseY(),
            0,
            emission->GetWidth(), emission->GetHeight()
        );

        renderer.SetColor(100, 100, 100, 100);
        renderer.DrawRect(affector->GetStartX(), affector->GetStartY(), affector->GetEndX() - affector->GetStartX(), affector->GetEndY() - affector->GetStartY());

        renderer.SetColor(0, 100, 255, 100);
        renderer.DrawRect(affector2->GetStartX(), affector2->GetStartY(), affector2->GetEndX() - affector2->GetStartX(), affector2->GetEndY() - affector2->GetStartY());

        // Refrescamos la pantalla 
        screen.Refresh();
    } 

	rm.FreeResources();

    return 0; 
}