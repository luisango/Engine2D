#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>
#include <time.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const bool FULLSCREEN = false;

void randomizeColor(Sprite * spr)
{
    spr->SetColor(
        Random(0, 255), // r
        Random(0, 255), // g
        Random(0, 255), // b
        Random(0, 255)  // a
    );
}

int main(int argc, char* argv[])
{ 
    Screen& screen            = Screen::Instance();
    const Renderer& renderer  = Renderer::Instance();
    ResourceManager& rm       = ResourceManager::Instance(); 

	srand(time(NULL));

    screen.Open(WIDTH, HEIGHT, FULLSCREEN); 

    // Load speed
    //             v------ (-1) porque el punto inicial colisiona con 0 y cambia la velocidad
    int speed_x = 0;//-1 * Random(128, 255);
    int speed_y = 0;//-1 * Random(128, 255);

    // Load font & create sprite
    Font   * font_mono   = rm.LoadFont("data/arial16.png");
    Sprite * sprite_mono = new Sprite(font_mono);

    // Set blend mode by default
    sprite_mono->SetBlendMode(Renderer::BlendMode::ALPHA);

    // Set initial color
    randomizeColor(sprite_mono);

    // Set string
	String text = "Luisango #1";

    // Get width and heigth
    double text_width  = font_mono->GetTextWidth(text);
    double text_height = font_mono->GetTextHeight(text);
    
    // Set initial position
	sprite_mono->SetX(0);
	sprite_mono->SetY(0);

	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{
		// Clear
		renderer.Clear(0, 0, 0);
		
        sprite_mono->MoveTo(
			sprite_mono->GetX() + speed_x, 
			sprite_mono->GetY() + speed_y, 
			speed_x, 
			speed_y
		);
		
        // Update
        //sprite_mono->Update(screen.ElapsedTime());

		// Colisiones
        if ((int) sprite_mono->GetX() < 0) {
			speed_x *= -1;
            sprite_mono->SetX(0);
            randomizeColor(sprite_mono);
        }

        if ((int) sprite_mono->GetX() + text_width > WIDTH) {
            speed_x *= -1;
            sprite_mono->SetX(WIDTH - text_width);
            randomizeColor(sprite_mono);
        }
        
        if ((int) sprite_mono->GetY() < 0) {
            speed_y *= -1;
            sprite_mono->SetY(0);
            randomizeColor(sprite_mono);
        }

        if ((int) sprite_mono->GetY() + text_height > HEIGHT) {
            speed_y *= -1;
            sprite_mono->SetY(HEIGHT - text_height);
            randomizeColor(sprite_mono);
        }

		screen.SetTitle("SPEED X = " + String::FromFloat(speed_x) + " SPEED Y = "+ String::FromFloat(speed_y));

		renderer.SetColor(
			sprite_mono->GetRed(),
			sprite_mono->GetGreen(),
			sprite_mono->GetBlue(),
			sprite_mono->GetAlpha()
		);

		renderer.SetColor(255, 255, 255, 255);

		((Font *) sprite_mono->GetImage())->Render(text, sprite_mono->GetX(), sprite_mono->GetY());

        // Refrescamos la pantalla 
        screen.Refresh(); 
    } 

	rm.FreeResources();

    return 0; 
}