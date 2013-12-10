#include "../include/parallaxscene.h"
#include "../include/image.h"
#include "../include/screen.h"

void ParallaxScene::Update(double elapsed, Map* map)
{
	Scene::Update(elapsed, map);

    if (backLayer) {
	    backX += autoBackSpeedX * elapsed;
	    backY += autoBackSpeedY * elapsed;
    }

    if (frontLayer) {
        frontX += autoFrontSpeedX * elapsed;
        frontY += autoFrontSpeedY * elapsed; 
    }
}

void ParallaxScene::RenderBackground() const
{
    if (backLayer)
	    Renderer::Instance().DrawTiledImage(
		    backLayer, 
		    0, 0, 
		    Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), 
		    -backX + ( relFrontSpeedX * GetCamera().GetX() ), 
            -backY + ( relFrontSpeedY * GetCamera().GetY() )
	    );

    if (frontLayer)
	    Renderer::Instance().DrawTiledImage(
		    frontLayer, 
		    0, 0, 
		    Screen::Instance().GetWidth(), Screen::Instance().GetHeight(),
		    -frontX + ( relFrontSpeedX * GetCamera().GetX() ), 
            -frontY + ( relFrontSpeedY * GetCamera().GetY() )
	    );
}