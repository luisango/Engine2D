#include "../include/mapscene.h"
#include "../include/map.h"
#include "../include/sprite.h"

void MapScene::RenderAfterBackground() const {
	// Metodo padre
	ParallaxScene::RenderAfterBackground();

	// Dibujamos el mapa
	map->Render();
}
