#ifndef UGINE_MAP_H
#define UGINE_MAP_H

#include "array.h"
#include "string.h"
#include "types.h"

class Collision;
class Image;

class Map {
public:
    Map(const String& filename, uint16 firstColId = 0);

    virtual const String& GetFilename() const { return filename; }
    virtual bool IsValid() const { return valid; }
    virtual void Render() const;
    virtual bool CheckCollision(const Collision* collision) const;
    virtual const Image* GetImage() const { return image; }
    virtual Image* GetImage() { return image; }
    virtual uint32 GetWidth() const { return width * tileWidth; }
    virtual uint32 GetHeight() const { return height * tileHeight; }
    virtual uint16 GetTileWidth() const { return tileWidth; }
    virtual uint16 GetTileHeight() const { return tileHeight; }
    virtual uint16 GetColumns() const { return width; }
    virtual uint16 GetRows() const { return height; }
    virtual int32 GetTileId(uint16 column, uint16 row) const { return tileIds[row*GetColumns() + column]; }
    virtual double GetGroundY(double x, double y) const;
    virtual uint16 GetFirstColId() const { return firstColId; }
private:
    bool valid;
    String filename;
    uint16 width, height;
    uint16 tileWidth, tileHeight;
    String imageFile;
    Image* image;
    Array<int32> tileIds;
    uint16 firstColId;
};

#endif
