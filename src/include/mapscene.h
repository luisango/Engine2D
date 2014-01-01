#ifndef UGINE_MAPSCENE_H
#define UGINE_MAPSCENE_H

#include "parallaxscene.h"

class Map;

class MapScene : public ParallaxScene {
public:
    MapScene(Map* map, Image* imageBack = 0, Image* imageFront = 0) : ParallaxScene(imageBack, imageFront), map(map) {}
    virtual const Map* GetMap() const { return map; }

    virtual void Update(double elapsed) { ParallaxScene::Update(elapsed, map); }
protected:
    virtual void RenderAfterBackground() const;
private:
    Map* map;
};

#endif
