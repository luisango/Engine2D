#include "../include/parallaxscene.h"
#include "../include/image.h"
#include "../include/screen.h"

void ParallaxScene::Update(double elapsed, Map* map)
{
	Scene::Update(elapsed, map);

	backX += (autoBackSpeedX + ( relBackSpeedX * GetCamera().GetX() )) * elapsed;
	backY += (autoBackSpeedY + ( relBackSpeedY * GetCamera().GetY() )) * elapsed;

	frontX += (autoFrontSpeedX + ( relFrontSpeedX * GetCamera().GetX() )) * elapsed;
	frontY += (autoFrontSpeedY + ( relFrontSpeedY * GetCamera().GetY() )) * elapsed;
}

void ParallaxScene::RenderBackground() const
{
	Renderer::Instance().DrawTiledImage(
		backLayer, 
		0, 0, 
		Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), 
		backX, backY
	);

	Renderer::Instance().DrawTiledImage(
		frontLayer, 
		0, 0, 
		Screen::Instance().GetWidth(), Screen::Instance().GetHeight(),
		frontX, frontY
	);
}