#include "../include/collisionpixeldata.h"

extern "C" unsigned char* stbi_load(const char* filename, int* x, int* y, int* comp, int req_comp);
extern "C" void stbi_image_free(void* buffer);

CollisionPixelData::CollisionPixelData( const String& filename )
{
	this->filename = filename;
	width = 0;
	height = 0;
	data = NULL;

	int iWidth = 0;
	int iHeight = 0;
	unsigned char* buffer = stbi_load(filename.ToCString(), &iWidth, &iHeight, NULL, 4);

	if (buffer) {
		width = (uint16)iWidth;
		height = (uint16)iHeight;
		data = new bool[iWidth * iHeight];

		for (int j = 0; j < iHeight; j++)
			for (int i = 0; i < iWidth; i++)
			{
				if (buffer[j * iWidth * 4 + i * 4 + 3] != 0)
					data[j * iWidth + i] = true;
				else
					data[j * iWidth + i] = false;
			}

		free( buffer );
	}
}

CollisionPixelData::~CollisionPixelData()
{
	if (data)
		delete[] data;
}

bool CollisionPixelData::IsValid() const
{
	if (data)
		return true;
	else
		return false;
}

const String& CollisionPixelData::GetFilename() const
{
	return filename;
}

uint16 CollisionPixelData::GetWidth() const
{
	return width;
}

uint16 CollisionPixelData::GetHeight() const
{
	return height;
}

bool CollisionPixelData::GetData( uint32 x, uint32 y ) const
{
	return data[y * width + x];
}
