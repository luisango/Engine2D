#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;

// Circle options
const int CIRCLE_SIDES = 64;
const int CIRCLE_RADIUS = 10;
const int CIRCLE_ANGLE_SPEED = 1;
const int CIRCLE_DISTANCE = 40;

// Square options
const int SQUARE_C_SIDE = 12;

int main(int argc, char* argv[])
{ 
    Screen::Instance().Open(WIDTH, HEIGHT, false); 

    // Tarea: Cargar la imagen "data/ball.png"
    Image * img = ResourceManager::Instance().LoadImage("data/ball.png");

	double angle = 0;
	double scale = 1;
	double scale_step = 0.5;
	double scale_state = 1;

    // Tarea: centrar la imagen
    img->SetMidHandle();
	
    while(Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC))
    { 
        // TAREA: Actualizar ángulo y escala de la imagen
		if (scale_state) {
			if (scale + scale_step < 5)
				scale += scale_step * Screen::Instance().ElapsedTime();
			else
				scale_state = 0;
		} else {
			if (scale - scale_step > 1)
				scale -= scale_step * Screen::Instance().ElapsedTime();
			else
				scale_state = 1;
		}
		
		Screen::Instance().SetTitle("SCALE = " + String::FromFloat(img->GetWidth()*scale));
        // TAREA: Limpiar pantalla y dibujar la imagen
        Renderer::Instance().Clear();
		
		Renderer::Instance().DrawImage(img, WIDTH/2, HEIGHT/2, 0, img->GetWidth()*scale, img->GetHeight()*scale, WrapValue(angle, 360));

        // Refrescamos la pantalla 
        Screen::Instance().Refresh(); 

		angle += 20 * Screen::Instance().ElapsedTime();
    } 

    ResourceManager::Instance().FreeResources();

    return 0; 
}