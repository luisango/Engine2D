#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const bool FULLSCREEN = false;

int main(int argc, char* argv[])
{ 
    Screen& screen            = Screen::Instance();
    const Renderer& renderer  = Renderer::Instance();
    ResourceManager& rm       = ResourceManager::Instance(); 

    screen.Open(WIDTH, HEIGHT, FULLSCREEN); 

	// Tarea: Cargar la imagen "data/ball.png"
    Image * cursor = rm.LoadImage("data/pizza_cursor.png");

    Image * tile_floor    = rm.LoadImage("data/tile_floor.png");
    Image * tile_palmtree = rm.LoadImage("data/tile_palmtree.png");

	Image * img = rm.LoadImage("data/alien.png");
	Sprite * sprite = new Sprite(img);
    sprite->SetBlendMode(Renderer::BlendMode::ALPHA);

	double scale = 1;//0.5;
	double scale_increment = 0.1;
    
	double speed_x = 0;
	double speed_y = 0;

    sprite->SetX(WIDTH / 2);
    sprite->SetY(HEIGHT / 2);

	// Tarea: centrar la imagen
	img->SetMidHandle();
    
	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{ 
		int32 mouse_x = screen.GetMouseX();
		int32 mouse_y = screen.GetMouseY();

        sprite->Update(screen.ElapsedTime());

		// TAREA: Actualizar �ngulo y escala de la imagen
		scale += scale_increment * screen.ElapsedTime();
        
		if (scale >= 1.5) {
			scale = 1.5;
			scale_increment = scale_increment * -1;
		}

		if (scale <= 0.8) {
			scale = 0.8;
			scale_increment = scale_increment * -1;
		}
        
		sprite->SetScale(scale, scale);

        if (mouse_x > sprite->GetX())
            sprite->RotateTo(-15, 10);

        if (mouse_x < sprite->GetX())
            sprite->RotateTo(15, 10);

        if (mouse_x == sprite->GetX())
            sprite->RotateTo(0, 10);

		if ( IsBetweenOrEqual(mouse_x, 0, WIDTH) && IsBetweenOrEqual(mouse_y, 0, HEIGHT) ) {
			speed_x = Abs(mouse_x - sprite->GetX());
			speed_x = (speed_x < 4) ? 4 : speed_x;
			
			speed_y = Abs(mouse_y - sprite->GetY());
			speed_y = (speed_y < 4) ? 4 : speed_y;

			if ( (mouse_x == sprite->GetX()) && (mouse_y == sprite->GetY()) )
				speed_x = speed_y = 0;
			else 
				sprite->MoveTo(mouse_x, mouse_y, speed_x, speed_y);
		}

        screen.SetTitle(
			"SCALE = " + String::FromInt((int)img->GetWidth()*scale) + 
			" ANGLE = " + String::FromInt((int) sprite->GetAngle()) +
			" SPEED = " + String::FromInt((int) sqrt(pow(speed_x, 2) + pow(speed_y, 2)))
		);

		// TAREA: Limpiar pantalla y dibujar la imagen
        renderer.Clear(130, 160, 250);

        // DRAW BACK
        renderer.DrawImage(tile_palmtree, WIDTH - 200, HEIGHT - tile_floor->GetHeight() - tile_palmtree->GetHeight(), 0, tile_palmtree->GetWidth(), tile_palmtree->GetHeight(), 0);
        
        // DRAW MO�O�O
		sprite->Render();

        // DRAW FRONT
        for (int i = 0; i < WIDTH + tile_floor->GetWidth(); i += tile_floor->GetWidth())
        {
            renderer.DrawImage(tile_floor, i, HEIGHT - tile_floor->GetHeight(), 0, tile_floor->GetWidth(), tile_floor->GetHeight(), 0);
        }

        // DRAW CURSOR
        renderer.DrawImage(cursor, screen.GetMouseX(), screen.GetMouseY(), 0, cursor->GetWidth(), cursor->GetHeight(), 0);

        // Refrescamos la pantalla 
        screen.Refresh(); 
    } 

	rm.FreeResources();

    return 0; 
}