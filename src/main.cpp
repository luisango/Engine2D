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

    double cch = 0; // Circle Center Horizontal (para dibujar los circulos relativo a este punto)
	double ccv = 0; // Circle Center Vertical

    double dist  = 28;
    double radio = 32;

    Image * img_box   = rm.LoadImage("data/box.jpg");
    Image * img_light = rm.LoadImage("data/light.png");

    GLenum src[] = { GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
    GLenum dst[] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

    while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
    { 
        // TAREA: Pintar franjas de pantalla
        renderer.Clear();
        renderer.SetColor(255, 255, 255, 255);

        ccv = img_box->GetHeight();
        for (int i = 0; i < 6; i++) 
        {
            cch = img_box->GetWidth();

            for (int j = 0; j < 6; j++) 
            {
                // Cambiamos a solid
                renderer.SetBlendMode(Renderer::BlendMode::SOLID);

                // Pintamos la caja
                img_box->SetMidHandle();
                renderer.DrawImage(img_box,   ccv, cch, 0, img_box->GetWidth(),   img_box->GetHeight(),   0);

                // Cambiamos al modo X,Y
                glBlendFunc(src[i], dst[j]);

                // Pintamos la luz
                img_light->SetMidHandle();
                renderer.DrawImage(img_light, ccv, cch, 0, img_light->GetWidth(), img_light->GetHeight(), 0);

                cch += img_box->GetWidth();
            }

            ccv += img_box->GetHeight();
        }
        
        /*------------------------------------------------------------------------------------------------------------------ 
        // TAREA: Pintar franjas de pantalla
        renderer.Clear();
        renderer.SetColor(255, 255, 255, 255);
        renderer.DrawRect(WIDTH / 3, 0, WIDTH / 3, HEIGHT);

        // TAREA: Pintar círculos en modo SOLID 
        renderer.SetBlendMode(Renderer::BlendMode::SOLID);
        cch = WIDTH / 2;
        ccv = HEIGHT / 6;

        // RED
        renderer.SetColor(255, 0, 0, 255);
        renderer.DrawEllipse(cch, ccv - dist/2, radio, radio);

        // GREEN
        renderer.SetColor(0, 255, 0, 255);
        renderer.DrawEllipse(cch - dist/1.7, ccv + dist/2, radio, radio);

        // BLUE
        renderer.SetColor(0, 0, 255, 255);
        renderer.DrawEllipse(cch + dist/1.7, ccv + dist/2, radio, radio);

        // TAREA: Pintar círculos en modo ALPHA 
        renderer.SetBlendMode(Renderer::BlendMode::ALPHA);
        cch = WIDTH / 6;
        ccv = HEIGHT / 2;

        // RED
        renderer.SetColor(255, 0, 0, 128);
        renderer.DrawEllipse(cch, ccv - dist/2, radio, radio);

        // GREEN
        renderer.SetColor(0, 255, 0, 128);
        renderer.DrawEllipse(cch - dist/1.7, ccv + dist/2, radio, radio);

        // BLUE
        renderer.SetColor(0, 0, 255, 128);
        renderer.DrawEllipse(cch + dist/1.7, ccv + dist/2, radio, radio);

        // TAREA: Pintar círculos en modo MULTIPLICATIVE 
        renderer.SetBlendMode(Renderer::BlendMode::MULTIPLICATIVE);
        cch = WIDTH / 2;
        ccv = HEIGHT - HEIGHT / 6;

        // RED
        renderer.SetColor(255, 0, 0, 255);
        renderer.DrawEllipse(cch, ccv - dist/2, radio, radio);

        // GREEN
        renderer.SetColor(0, 255, 0, 255);
        renderer.DrawEllipse(cch - dist/1.7, ccv + dist/2, radio, radio);

        // BLUE
        renderer.SetColor(0, 0, 255, 255);
        renderer.DrawEllipse(cch + dist/1.7, ccv + dist/2, radio, radio);

        // TAREA: Pintar círculos en modo ADDITIVE
        renderer.SetBlendMode(Renderer::BlendMode::ADDITIVE);
        cch = WIDTH / 6 * 5;
        ccv = HEIGHT / 2;

        // RED
        renderer.SetColor(255, 0, 0, 255);
        renderer.DrawEllipse(cch, ccv - dist/2, radio, radio);

        // GREEN
        renderer.SetColor(0, 255, 0, 255);
        renderer.DrawEllipse(cch - dist/1.7, ccv + dist/2, radio, radio);

        // BLUE
        renderer.SetColor(0, 0, 255, 255);
        renderer.DrawEllipse(cch + dist/1.7, ccv + dist/2, radio, radio);
        ------------------------------------------------------------------------------------------------------------------ */

        // Refrescamos la pantalla 
        screen.Refresh(); 
    } 

    return 0; 
}