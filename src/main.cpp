#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <math.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const bool FULLSCREEN = false;
int SPEED = 400;
    
int main(int argc, char* argv[])
{ 
    Screen& screen           = Screen::Instance();
    const Renderer& renderer = Renderer::Instance();
    ResourceManager& rm      = ResourceManager::Instance(); 

    screen.Open(WIDTH, HEIGHT, FULLSCREEN); 
    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetMousePos(WIDTH / 2, HEIGHT / 2);

    Map* map = rm.LoadMap("data/caves.map");

    Image* img_alien = rm.LoadImage("data/char.mdl", 8);   
    Image* img_alien2 = rm.LoadImage("data/ghost.mdl");  
    Image* img_back  = rm.LoadImage("data/caves.bg");
    Image* img_torch = rm.LoadImage("data/torch.fire");
    Image* img_torch_light = rm.LoadImage("data/torch.light");

    Font* font = rm.LoadFont("data/monospaced.font");

    MapScene* scene = new MapScene(map, img_back);
    scene->SetRelativeBackSpeed(.5, .5);
    scene->SetRelativeFrontSpeed(.3, .3);
    scene->SetAutoBackSpeed(0, 0);
    scene->SetAutoFrontSpeed(0, 0);

    Sprite* spr_torch_light = scene->CreateSprite(img_torch_light);

    Sprite* spr_alien = scene->CreateSprite(img_alien);
    CollisionPixelData* cpd = rm.LoadCollisionPixelData("data/char.col");
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

    // TORCH PROPERTIES
    int torch_visibility = 200;
    int torch_alpha_max = 110;
    int torch_alpha_min = 50;
    int torch_alpha_range = 10;
    int torch_alpha = torch_alpha_max;

    img_torch_light->SetMidHandle();
    spr_torch_light->SetBlendMode(Renderer::BlendMode::ADDITIVE);
    spr_torch_light->SetColor(255, 255, 255, 128);

    img_torch->SetMidHandle();

    Emitter* emitter = scene->CreateEmitter(img_torch, true);
    emitter->SetBlendMode(Renderer::BlendMode::ADDITIVE);
    emitter->SetRate(50, Random(70, 150));
    emitter->SetVelocityX(Random(-30, -10), Random(10, 30));
    emitter->SetVelocityY(Random(-250, -120), 10);
    emitter->SetAngularVelocity(0, 0);
    emitter->SetLifetime(1, Random(3, 7));
    emitter->SetMinColor(150, 0, 0);
    emitter->SetMaxColor(255, 100, 50);

    // Default
    emitter->SetPosition(-1000, -1000);
    spr_torch_light->SetPosition(-1000, -1000);

    // Egg properties
    img_alien2->SetMidHandle();
    Emitter* emitter2 = scene->CreateEmitter(img_alien2, true);
    emitter2->SetBlendMode(Renderer::BlendMode::ADDITIVE);
    emitter2->SetRate(70, Random(70, 100));
    emitter2->SetAngularVelocity(-5, 5);
    emitter2->SetLifetime(1, Random(3, 10));
    emitter2->SetMinColor(50, 50, 150);
    emitter2->SetMaxColor(50, 50, 250);

    // SCORE VARS
    int init = 0;
    int score = 1;
    int final_score = 0;
    int best_score = 0;
    int top_score = 5000;

    // TINT VARS
    int min_bg_tint = 30;
    int max_bg_tint = 200;
    int bg_tint_op = map->GetHeight() / max_bg_tint * min_bg_tint;

    int min_map_tint = 100;
    int max_map_tint = 255;

    // GAME STATES
    enum GameState {
        BEGIN,
        PLAY,
        END
    } state, next_state;

    state = next_state = GameState::BEGIN;


    // BONES
    SkeletonSprite * spriteBones = new SkeletonSprite("data/animation.xml");
    spriteBones->SetPosition(0, 0);
	spriteBones->SetFPS(32);


	while(screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{   
        state = next_state;

        switch (state)
        {
        case BEGIN:
            {
                renderer.Clear(0, 0, 0);

                String title_text = "SUPAMAZE";
                double fs1_x = WIDTH / 2 - font->GetTextWidth(title_text) / 2;
                double fs1_y = HEIGHT / 4;

                String credits_text = "by Luis Lalueza";
                double fs2_x = WIDTH / 2 - font->GetTextWidth(credits_text) / 2;
                double fs2_y = HEIGHT / 4 + font->GetHeight() + 6;

                String start_text = "Use arrow keys to move. Press SPACE to start.";
                double fs3_x = WIDTH / 2 - font->GetTextWidth(start_text) / 2;
                double fs3_y = HEIGHT * 3/ 4;

                renderer.SetColor(255, 255, 255, 255);
                renderer.DrawText(font, title_text, fs1_x, fs1_y);
                renderer.SetColor(150, 150, 150, 255);
                renderer.DrawText(font, credits_text, fs2_x, fs2_y);
                renderer.SetColor(255, 255, 255, 255);
                renderer.DrawText(font, start_text, fs3_x, fs3_y);

                if (screen.KeyPressed(GLFW_KEY_LSHIFT)) {
                    spr_alien->SetColor(50, 50, 250);
                    emitter2->Start();
                    SPEED = 600;
                }

                if (screen.KeyPressed(GLFW_KEY_SPACE)) {
                    init = glfwGetTime() * 10;
                    next_state = GameState::PLAY;
                    emitter->Start();
                }

                spriteBones->Update(screen.ElapsedTime());
                
		        spriteBones->Render();

            }
            break;

        case PLAY:
            {
                to_x = spr_alien->GetX();
                to_y = spr_alien->GetY();

                // Update trail
                emitter2->SetPosition(
                    to_x + spr_alien->GetImage()->GetWidth() * spr_alien->GetScaleX() / 2, 
                    to_y + spr_alien->GetImage()->GetHeight() * spr_alien->GetScaleY() / 2
                );
                emitter2->SetVelocityX(Random(-30, -1), Random(1, 30));
                emitter2->SetVelocityY(Random(-30, -1), Random(1, 30));

                // Update score
                if (score > 0)
                    score = top_score - glfwGetTime() * 10 + init;
                else
                    score = 0;

                // Update sprite
                if (screen.KeyPressed(GLFW_KEY_LEFT)) {
                    to_x -= SPEED;
                }
                if (screen.KeyPressed(GLFW_KEY_RIGHT)) {
                    to_x += SPEED;
                }
                if (screen.KeyPressed(GLFW_KEY_UP)) {
                    to_y -= SPEED;
                }
                if (screen.KeyPressed(GLFW_KEY_DOWN)) {
                    to_y += SPEED;
                }

                // Move alien
                spr_alien->MoveTo(to_x, to_y + SPEED * 0.003, SPEED);

                // Update scene background tint
                int bg_tint = max_bg_tint - (((spr_alien->GetY() - bg_tint_op)  * max_bg_tint) / map->GetHeight());
                if (bg_tint > max_bg_tint)
                    bg_tint = max_bg_tint;

                scene->SetBackgroundTint(
                    bg_tint,
                    bg_tint,
                    bg_tint
                );
                
                int map_tint = bg_tint + (min_map_tint - min_bg_tint);

                if (map_tint < min_map_tint) {
                    map_tint = min_map_tint;
                } else if (map_tint > max_map_tint) {
                    map_tint = max_map_tint;
                }

                map->SetMapTint(
                    map_tint,
                    map_tint,
                    map_tint
                );

                // Update torch position
                if (PointInRect(533, 5955, cam.GetX() - torch_visibility, cam.GetY()- torch_visibility, WIDTH + torch_visibility, HEIGHT + torch_visibility)) {
                    spr_torch_light->SetPosition(533, 5955);
                    emitter->SetPosition(533, 5955);
                } else if (PointInRect(1351, 4756, cam.GetX() - torch_visibility, cam.GetY()- torch_visibility, WIDTH + torch_visibility, HEIGHT + torch_visibility)) {
                    spr_torch_light->SetPosition(1351, 4756);
                    emitter->SetPosition(1351, 4756);
                } else if (PointInRect(155, 4945, cam.GetX() - torch_visibility, cam.GetY()- torch_visibility, WIDTH + torch_visibility, HEIGHT + torch_visibility)) {
                    spr_torch_light->SetPosition(155, 4945);
                    emitter->SetPosition(155, 4945);
                } else if (PointInRect(2171, 5764, cam.GetX() - torch_visibility, cam.GetY()- torch_visibility, WIDTH + torch_visibility, HEIGHT + torch_visibility)) {
                    spr_torch_light->SetPosition(2171, 5764);
                    emitter->SetPosition(2171, 5764);
                } else if (PointInRect(2485, 4126, cam.GetX() - torch_visibility, cam.GetY()- torch_visibility, WIDTH + torch_visibility, HEIGHT + torch_visibility)) {
                    spr_torch_light->SetPosition(2485, 4126);
                    emitter->SetPosition(2485, 4126);
                } else if (PointInRect(973, 3558, cam.GetX() - torch_visibility, cam.GetY()- torch_visibility, WIDTH + torch_visibility, HEIGHT + torch_visibility)) {
                    spr_torch_light->SetPosition(973, 3558);
                    emitter->SetPosition(973, 3558);
                } else if (PointInRect(2612, 2487, cam.GetX() - torch_visibility, cam.GetY()- torch_visibility, WIDTH + torch_visibility, HEIGHT + torch_visibility)) {
                    spr_torch_light->SetPosition(2612, 2487);
                    emitter->SetPosition(2612, 2487);
                } else {
                    // Turn the lights off
                    spr_torch_light->SetColor(255, 255, 255, 0);
                    //emitter->Stop();
                }

                if (emitter->IsEmitting()) {
                    // Torch light animation
                    int torch_alpha_new = Random(torch_alpha_min, torch_alpha_max);

                    if (IsBetweenOrEqual(torch_alpha_new, torch_alpha - torch_alpha_range, torch_alpha + torch_alpha_range))
                        torch_alpha = torch_alpha_new;

                    spr_torch_light->SetColor(255, 255, 255, torch_alpha);
                }


                // Update scene
                scene->Update(screen.ElapsedTime());

                // Draw scene
                scene->Render();

                // Draw score
                renderer.SetColor(255, 255, 255, 255);
                renderer.DrawText(font, "Score: " + String::FromInt(score), cam.GetX() + 10, cam.GetY() + 10);

                // Win condition
                if (IsBetweenOrEqual(spr_alien->GetX(), 650, 700) && IsBetweenOrEqual(spr_alien->GetY(), 5900, 5995)) {
                    if (!final_score)
                        final_score = score;

                    best_score = (final_score > best_score) ? final_score : best_score;

                    next_state = GameState::END;
                }
            }
            break;

        case END:
            {
                renderer.Clear();

                String again_text = "Press SPACE to play again or ESC to exit";
                double fs1_x = cam.GetX() + WIDTH / 2 - font->GetTextWidth(again_text) / 2;
                double fs1_y = cam.GetY() + HEIGHT / 4;

                String final_text = "FINAL SCORE: " + String::FromInt(final_score);
                double fs2_x = cam.GetX() + WIDTH / 2 - font->GetTextWidth(final_text) / 2;
                double fs2_y = cam.GetY() + HEIGHT / 2;

                String best_text = "BEST SCORE: " + String::FromInt(best_score);
                double fs3_x = cam.GetX() + WIDTH / 2 - font->GetTextWidth(best_text) / 2;
                double fs3_y = cam.GetY() + HEIGHT / 2 + font->GetHeight() + 6;
                
                renderer.SetColor(255, 255, 255, 255);
                renderer.DrawText(font, again_text, fs1_x, fs1_y);

                renderer.SetColor(Random(100, 255), Random(100, 255), Random(100, 255), 255);
                renderer.DrawText(font, final_text, fs2_x, fs2_y);
                renderer.DrawText(font, best_text, fs3_x, fs3_y);

                if (screen.KeyPressed(GLFW_KEY_SPACE)) {
                    spr_alien->SetX(WIDTH / 2);
                    spr_alien->SetY(HEIGHT / 2);

                    init = glfwGetTime() * 10;
                    score = 1;
                    final_score = 0;
                    next_state = GameState::PLAY;
                }
            }
            break;
        }

        // Refrescamos la pantalla 
        screen.Refresh();
    } 

	rm.FreeResources();

    return 0; 
}