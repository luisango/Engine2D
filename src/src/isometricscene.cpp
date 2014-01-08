#include "../include/isometricscene.h"
#include "../include/isometricmap.h"

IsometricScene::IsometricScene(IsometricMap* map, Image* imageBack, Image* imageFront) 
    : MapScene((Map*) map, imageBack, imageFront) 
{
    map->GenerateLayerSprites(this);
}

IsometricSprite* IsometricScene::CreateSprite(Image* image, Layer layer) {
    IsometricSprite* is = new IsometricSprite(image);
    AddSprite(is, layer);
    return is;
}

void IsometricScene::Update(double elapsed, Map* map) {
    MapScene::Update(elapsed);

    for (int i = 0; i < LAYER_COUNT; i++)
        GetSprites((Scene::Layer) i).Sort(CompareSprites);
}

bool IsometricScene::CompareSprites(Sprite*& first, Sprite*& second) {
    return first->GetY() < second->GetY();
}