#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

#define DIRECTION_LEFT 0
#define DIRECTION_UP 24
#define DIRECTION_RIGHT 40
#define DIRECTION_DOWN 56
#define ANIM_LENGTH 4
#define FRAME_WIDTH 8


inline void SetDirection(Sprite* spr, int direction) {
    spr->SetFrameRange(direction, direction+ANIM_LENGTH-1);
}


int main(int argc, char* argv[]) {
    Screen& screen = Screen::Instance();
    ResourceManager& resManager =  ResourceManager::Instance();

    screen.Open(800, 600, false);

    Image* playerImg = resManager.LoadImage("data/isoplayer.png", 8, 8);
    IsometricMap* map = resManager.LoadIsometricMap("data/isometric.tmx");

    playerImg->SetHandle(playerImg->GetWidth()/2, playerImg->GetHeight());
	
	IsometricScene scene(map);

    Sprite* player = scene.CreateSprite(playerImg);
    player->SetPosition(map->GetTileWidth()*1.5, map->GetTileHeight()*1.5);

    Camera& cam = scene.GetCamera();
    cam.FollowSprite(player);

	uint16 firstColId = 3;
    while (screen.IsOpened()  &&  !screen.KeyPressed(GLFW_KEY_ESC)) {
		// Actualizamos movimiento y animacion del jugador
        if ( !player->IsMoving() ) {
            double toX = player->GetX();
            double toY = player->GetY();
            if (screen.KeyPressed(GLFW_KEY_LEFT)) { 
                toX -= scene.GetMap()->GetTileWidth(); 
                SetDirection(player, DIRECTION_LEFT); 
            }

            if (screen.KeyPressed(GLFW_KEY_RIGHT)) { 
                toX += scene.GetMap()->GetTileWidth(); 
                SetDirection(player, DIRECTION_RIGHT); 
            }

            if (screen.KeyPressed(GLFW_KEY_UP)) { 
                toY -= scene.GetMap()->GetTileHeight(); 
                SetDirection(player, DIRECTION_UP); 
            }

            if (screen.KeyPressed(GLFW_KEY_DOWN)) { 
                toY += scene.GetMap()->GetTileHeight(); 
                SetDirection(player, DIRECTION_DOWN); 
            }
			
			// Nos movemos si la tile de destino no est· bloqueada
            int32 tilex = toX/map->GetTileWidth();
            int32 tiley = toY/map->GetTileHeight();
            if ( map->GetTileId(tilex, tiley) < firstColId  &&  map->GetLayerId(tilex, tiley) < firstColId )
                player->MoveTo(toX, toY, 256, 256);
		}

        if ( player->IsMoving() ) {
            player->SetFPS(16);
		} else {
            player->SetFPS(0);
            player->SetCurrentFrame(player->GetCurrentFrame() - (player->GetCurrentFrame()%FRAME_WIDTH));
		}
		
		// Actualizamos escena
        scene.Update(screen.ElapsedTime());

		// Dibujamos
        scene.Render();
        screen.Refresh();
	}

    resManager.FreeResources();

	return 0;
}
