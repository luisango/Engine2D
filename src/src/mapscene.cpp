#include "../include/mapscene.h"
#include "../include/map.h"
#include "../include/sprite.h"

void MapScene::RenderAfterBackground() const {
	ParallaxScene::RenderAfterBackground();

	map->Render();
}
