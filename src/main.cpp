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

    double distance = 0;
    double angle = 0;
    double angle_shown = 0;
    double circle_x = 0;
    double circle_y = 0;
    int mouse_x = 0;
    int mouse_y = 0;

    while(Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC))
    { 
        Renderer::Instance().Clear(0,0,0);
        glfwGetMousePos(&mouse_x, &mouse_y);
    

        // TAREA: Calcular coordenadas del círculo 
        circle_x = mouse_x + CIRCLE_DISTANCE * DegCos(angle);
        circle_y = mouse_y - CIRCLE_DISTANCE * DegSin(angle);
        

        angle += CIRCLE_ANGLE_SPEED;
        angle = WrapValue(angle, 360);
        


        // TAREA: Escribir título de la ventana 
        angle_shown = Angle(mouse_x, mouse_y, circle_x, circle_y);
        distance = Distance(WIDTH/2, HEIGHT/2, mouse_x, mouse_y);
        Screen::Instance().SetTitle("Angulo: " + String::FromFloat(angle_shown) + " Dist: " + String::FromFloat(distance));

        // TAREA: Dibujar primitivas 
        Renderer::Instance().SetColor(255, 0, 0, 0);
        Renderer::Instance().DrawRect(WIDTH/2-SQUARE_C_SIDE, HEIGHT/2-SQUARE_C_SIDE, SQUARE_C_SIDE*2, SQUARE_C_SIDE*2);

        Renderer::Instance().SetColor(255, 255, 255, 0);
        Renderer::Instance().DrawRect(mouse_x-SQUARE_C_SIDE/2, mouse_y-SQUARE_C_SIDE/2, SQUARE_C_SIDE, SQUARE_C_SIDE);

        Renderer::Instance().SetColor(200, 200, 200, 0);
        Renderer::Instance().DrawEllipse(circle_x, circle_y, CIRCLE_RADIUS, CIRCLE_RADIUS);

        // Refrescamos la pantalla 
        Screen::Instance().Refresh(); 
    } 

    return 0; 
}