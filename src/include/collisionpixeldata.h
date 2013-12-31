#ifndef _UGINE_COLLISIONPIXELDATA_H_
#define _UGINE_COLLISIONPIXELDATA_H_

#include "string.h"
#include "types.h"

class CollisionPixelData
{
public:
	CollisionPixelData(const String& filename);
	virtual ~CollisionPixelData();

	virtual bool IsValid() const;
	virtual const String& GetFilename() const;
	virtual uint16 GetWidth() const;
	virtual uint16 GetHeight() const;
	virtual bool GetData(uint32 x, uint32 y) const;
private:
	String filename;
	uint16 width, height;
	bool* data;
};

#endif
