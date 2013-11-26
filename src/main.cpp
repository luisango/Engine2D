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
	Image * img = rm.LoadImage("data/soccer_npot.png");
	Sprite * sprite = new Sprite(img);

	double angle = 0;
	double scale = 1;//0.5;
	double scale_increment = 2;

	// Tarea: centrar la imagen
	img->SetMidHandle();
        
	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{ 
		// TAREA: Actualizar ángulo y escala de la imagen
		scale += scale_increment * screen.ElapsedTime();
        
		if (scale >= 5) {
			scale = 5;
			scale_increment = scale_increment * -1;
		}

		if (scale <= 0.5) {
			scale = 0.5;
			scale_increment = scale_increment * -1;
		}

		angle += 30 * screen.ElapsedTime();
        
		sprite->SetScale(scale, scale);
		sprite->SetAngle(angle);

		screen.SetTitle("SCALE = " + String::FromFloat(img->GetWidth()*scale));
		// TAREA: Limpiar pantalla y dibujar la imagen
		renderer.Clear();
                
		sprite->Render();

		renderer.DrawImage(
			sprite->GetImage(), 
			WIDTH/2, HEIGHT/2, 
			sprite->GetCurrentFrame(), 
			sprite->GetImage()->GetWidth() * sprite->GetScaleX(), 
			sprite->GetImage()->GetHeight() * sprite->GetScaleY(), 
			sprite->GetAngle()
		);

        // Refrescamos la pantalla 
        screen.Refresh(); 
    } 

	rm.FreeResources();

    return 0; 
}