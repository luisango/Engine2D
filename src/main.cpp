#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const bool FULLSCREEN = false;
const int SPEED = 400;
    
int main(int argc, char* argv[])
{ 
    Screen& screen           = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();
    ResourceManager& rm      = ResourceManager::Instance(); 

    screen.Open(WIDTH, HEIGHT, FULLSCREEN); 
    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetMousePos(WIDTH / 2, HEIGHT / 2);

    Map* map = rm.LoadMap("data/map2.tmx");

    Image* img_alien   = rm.LoadImage("data/alienanim.png", 8);   
    Image* img_back    = rm.LoadImage("data/terrain_background.png");

    Font* fnt_score = rm.LoadFont("data/monospaced.png");

    MapScene* scene = new MapScene(map, img_back);
    scene->SetRelativeBackSpeed(.5, .5);
    scene->SetRelativeFrontSpeed(.3, .3);
    scene->SetAutoBackSpeed(0, 0);
    scene->SetAutoFrontSpeed(0, 0);

    Sprite* spr_alien = scene->CreateSprite(img_alien);
    CollisionPixelData* cpd = rm.LoadCollisionPixelData("data/aliencol.png");
    spr_alien->SetFPS(16);
    spr_alien->SetScale(4, 4);
    spr_alien->SetCollisionPixelData(cpd);
    spr_alien->SetPosition(192, 400);
    spr_alien->SetCollision(Sprite::COLLISION_PIXEL);

    Camera& cam = scene->GetCamera();
    cam.SetBounds(0, 0, scene->GetMap()->GetWidth(), scene->GetMap()->GetHeight());
    scene->GetCamera().FollowSprite(spr_alien);

    spr_alien->SetX(WIDTH / 2);
    spr_alien->SetY(HEIGHT / 2);

    double to_x = 0, to_y = 0;
    int init = glfwGetTime() * 10;
    int score = 1;
    int final_score = 0;
    int top_score = 3000;

	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{   
        to_x = spr_alien->GetX();
        to_y = spr_alien->GetY();

        // Update score
        if (score > 0)
            score = top_score - glfwGetTime() * 10 - init;
        else
            score = 0;

        // Update sprite
        if (screen.KeyPressed(GLFW_KEY_LEFT))
            to_x -= SPEED;
        if (screen.KeyPressed(GLFW_KEY_RIGHT))
            to_x += SPEED;
        if (screen.KeyPressed(GLFW_KEY_UP))
            to_y -= SPEED;
        if (screen.KeyPressed(GLFW_KEY_DOWN))
            to_y += SPEED;

        // Move alien
        spr_alien->MoveTo(to_x, to_y + SPEED * 0.003, SPEED);

        // Update scene
        scene->Update(screen.ElapsedTime());

        // Draw scene
        scene->Render();

        // Draw score
        renderer.SetColor(255, 255, 255, 255);
        renderer.DrawText(fnt_score, "Score: " + String::FromInt(score), cam.GetX() + 10, cam.GetY() + 10);

        // Win condition
        if (IsBetweenOrEqual(spr_alien->GetX(), 650, 780) && IsBetweenOrEqual(spr_alien->GetY(), 6000, 6150)) {
            if (!final_score)
                final_score = score;

            String final_text = "FINAL SCORE: " + String::FromInt(final_score);
            double fs_x = cam.GetX() + WIDTH / 2 - fnt_score->GetTextWidth(final_text) / 2;
            double fs_y = cam.GetY() + HEIGHT / 2;
            int border = 2;

            renderer.SetColor(0, 0, 0, 255);
            for (int i = -1 * border; i < border + 1; i++)
                for (int z = -1 * border; z < border + 1; z++)
                    renderer.DrawText(fnt_score, final_text, fs_x + i, fs_y + z);

            renderer.SetColor(Random(0, 255), Random(0, 255), Random(0, 255), 255);
            renderer.DrawText(fnt_score, final_text, fs_x, fs_y);
        }


        // Refrescamos la pantalla 
        screen.Refresh();
    } 

	rm.FreeResources();

    return 0; 
}