
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
    int speed_x = -1 * Random(128, 255);
    int speed_y = -1 * Random(128, 255);

    // Load font & create sprite
    Font   * font_mono   = rm.LoadFont("data/arial16.png");
    Sprite * sprite_mono = new Sprite(font_mono);

    // Set blend mode by default
    sprite_mono->SetBlendMode(Renderer::BlendMode::ALPHA);

    // Set initial color
    randomizeColor(sprite_mono);

    // Set string
	String text = "Hello, world!";

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
        sprite_mono->Update(screen.ElapsedTime());

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

		((Font *) sprite_mono->GetImage())->Render(text, sprite_mono->GetX(), sprite_mono->GetY());

        // Refrescamos la pantalla 
        screen.Refresh(); 
    } 

	rm.FreeResources();

    return 0; 
}

/*#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

#include "Windows.h"
#include "xinput.h"

#pragma comment(lib, "XInput9_1_0.lib")

const int WIDTH = 2560;
const int HEIGHT = 1440;
const bool FULLSCREEN = true;

int main(int argc, char* argv[])
{ 
    Screen& screen            = Screen::Instance();
    const Renderer& renderer  = Renderer::Instance();
    ResourceManager& rm       = ResourceManager::Instance(); 

    screen.Open(WIDTH, HEIGHT, FULLSCREEN); 

	// Tarea: Cargar la imagen "data/ball.png"
    Image * cursor = new Image("data/pizza_cursor.png");

    Image * tile_floor    = new Image("data/tile_floor.png");
    Image * tile_palmtree = new Image("data/tile_palmtree.png");

	Image * img = new Image("data/alien.png");
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
        // XINPUT STARTS 
        XINPUT_STATE state;
        memset(&state, 0, sizeof(state));

        XINPUT_VIBRATION vibration;
        memset(&vibration, 0, sizeof(vibration));

        XInputGetState(0, &state);

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
            Beep(4440, 100);

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
            vibration.wLeftMotorSpeed = 65535;
            vibration.wRightMotorSpeed = 65535;
        }

        XInputSetState(0, &vibration);


        float xPad = (float) state.Gamepad.sThumbLX / 32768;
        float yPad = (float) state.Gamepad.sThumbLY / 32768;
        // XINPUT ENDS 


		int32 mouse_x = screen.GetMouseX();
		int32 mouse_y = screen.GetMouseY();

        sprite->Update(screen.ElapsedTime());

		// TAREA: Actualizar ángulo y escala de la imagen
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
                sprite->MoveTo(sprite->GetX() + xPad * 10, sprite->GetY() - yPad * 10, 500, 500);
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
        
        // DRAW MOÑOÑO
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

*/