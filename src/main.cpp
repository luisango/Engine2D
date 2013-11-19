#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* argv[]) {
    //                                     Pantalla completa
    Screen::Instance().Open(WIDTH, HEIGHT, false);
    Screen::Instance().SetTitle("Práctica 1");
	
	while ( Screen::Instance().IsOpened() ) {
		// TAREA: Pintar primitivas
        Renderer::Instance().Clear(255,255,0);

		// Cambiamos el color de pintado
        Renderer::Instance().SetColor(255,0,0,127);

        // Pintamos el rectángulo
        Renderer::Instance().DrawRect(16, 16, WIDTH-16, HEIGHT-16);

		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	return 0;
}
