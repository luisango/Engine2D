#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

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

    screen.Open(WIDTH, HEIGHT, FULLSCREEN); 

    // Load speed
    //             v------ (-1) porque el punto inicial colisiona con 0 y cambia la velocidad
    int speed_x = -1 * Random(128, 255);
    int speed_y = -1 * Random(128, 255);

    // Load font & create sprite
    Font   * font_mono   = rm.LoadFont("data/monospaced.png");
    Sprite * sprite_mono = new Sprite(font_mono);

    // Set blend mode by default
    sprite_mono->SetBlendMode(Renderer::BlendMode::ALPHA);

    // Set initial color
    randomizeColor(sprite_mono);

    // Set string
    String text = "Hola, mundo";

    // Get width and heigth
    double text_width  = font_mono->GetTextWidth(text);
    double text_height = font_mono->GetTextHeight(text);
    
    // Set initial position
    int pos_x = 0;
    int pos_y = 0;

	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{ 
        // Update
        sprite_mono->Update(screen.ElapsedTime());
        
        if ((int) sprite_mono->GetX() <= 0) {
            // TODO: Cambiar velocidad
            sprite_mono->SetX(0);
            randomizeColor(sprite_mono);
        }

        if ((int) sprite_mono->GetX() + text_width >= WIDTH) {
            // TODO: Cambiar velocidad
            sprite_mono->SetX(WIDTH - text_width);
            randomizeColor(sprite_mono);
        }
        
        if ((int) sprite_mono->GetY() <= 0) {
            // TODO: Cambiar velocidad
            sprite_mono->SetY(0);
            randomizeColor(sprite_mono);
        }

        if ((int) sprite_mono->GetY() + text_height <= HEIGHT) {
            // TODO: Cambiar velocidad
            sprite_mono->SetY(HEIGHT - text_height);
            randomizeColor(sprite_mono);
        }

        if (!sprite_mono->IsMoving())
        {
            int goto_x = 100; // TODO: Completar esta logica
            int goto_y = 100;

            sprite_mono->MoveTo(speed_x, speed_y);
        }

        ((Font *) sprite_mono->GetImage())->Render(text, 300, 300);

        // Refrescamos la pantalla 
        screen.Refresh(); 
    } 

	rm.FreeResources();

    return 0; 
}