#ifndef UGINE_ISOMETRICMAP_H
#define UGINE_ISOMETRICMAP_H

#include "map.h"

class IsometricScene;

class IsometricMap : public Map {
public:
    IsometricMap(const String& filename, uint16 firstColId = 0);
    virtual void GenerateLayerSprites(IsometricScene* scene);
    virtual uint16 GetTileWidth() const { return Map::GetTileWidth()/2; }
    virtual void Render() const;
    virtual int32 GetLayerId(uint16 column, uint16 row) const { return topLayerIds[row*GetColumns() + column]; }
private:
    Array<int32> topLayerIds;
};

#endif
