#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* argv[])
{ 
    Screen& screen            = Screen::Instance();
    const Renderer& renderer  = Renderer::Instance();
    ResourceManager& rm       = ResourceManager::Instance(); 

    screen.Open(WIDTH, HEIGHT, false); 

	// Tarea: Cargar la imagen "data/ball.png"
	Image * img = rm.LoadImage("data/alien.png");
	Sprite * sprite = new Sprite(img);
    sprite->SetBlendMode(Renderer::BlendMode::ALPHA);

	double scale = 1;//0.5;
	double scale_increment = 2;
    
    sprite->SetX(WIDTH / 2);
    sprite->SetY(HEIGHT / 2);

    //sprite->SetScale(3, 3);

	// Tarea: centrar la imagen
	img->SetMidHandle();
    
	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{ 
        sprite->Update(screen.ElapsedTime());
		// TAREA: Actualizar ángulo y escala de la imagen
		/*scale += scale_increment * screen.ElapsedTime();
        
		if (scale >= 2) {
			scale = 2;
			scale_increment = scale_increment * -1;
		}

		if (scale <= 0.5) {
			scale = 0.5;
			scale_increment = scale_increment * -1;
		}
        
		sprite->SetScale(scale, scale);*/

        screen.SetTitle("SCALE = " + String::FromFloat(img->GetWidth()*scale) + " ANGLE = " + String::FromInt((int) sprite->GetAngle()) + " / " );

		// TAREA: Limpiar pantalla y dibujar la imagen
		renderer.Clear(130, 160, 250);

		sprite->Render();

        if (screen.GetMouseX() > sprite->GetX())
            sprite->RotateTo(-15, 10);

        if (screen.GetMouseX() < sprite->GetX())
            sprite->RotateTo(15, 10);

        if (screen.GetMouseX() == sprite->GetX())
            sprite->RotateTo(0, 10);

        if (!sprite->IsRotating()) 
        {
            int ang = (int) sprite->GetAngle();
            switch(ang) 
            {
            case 15:
                   
                break;
            case 345:
                   
                break;
            }
        }

        /*if (!sprite->IsRotating()) {
            angle = WrapValue(angle + 60, 360);
            sprite->RotateTo(angle, 30);
        }*/

        /*if (!sprite->IsMoving()) {
            int x = Abs(screen.GetMouseX());
            x = (x < WIDTH) ? x : 0;

            int y = Abs(screen.GetMouseY());
            y = (y < HEIGHT) ? y : 0;

            sprite->MoveTo(x, y, 30, 30);
        }*/

        // Refrescamos la pantalla 
        screen.Refresh(); 
    } 

	rm.FreeResources();

    return 0; 
}