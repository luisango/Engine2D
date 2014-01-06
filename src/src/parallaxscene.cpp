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
	Scene::RenderBackground();

	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	Renderer::Instance().SetColor(255, 255, 255, 255);
    
	if (backLayer)
	{
        Renderer::Instance().SetColor(backr_t, backg_t, backb_t, 255);

		double xPos = backX + relBackSpeedX * GetCamera().GetX();
		double yPos = backY + relBackSpeedY * GetCamera().GetY();
		Renderer::Instance().DrawTiledImage(backLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), xPos, yPos);
        Renderer::Instance().SetColor(255, 255, 255, 255);
	}
	if (frontLayer)
	{
		double xPos = frontX + relFrontSpeedX * GetCamera().GetX();
		double yPos = frontY + relFrontSpeedY * GetCamera().GetY();
		Renderer::Instance().DrawTiledImage(frontLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), xPos, yPos);
	}
}