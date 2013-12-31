#include "../include/collisionmanager.h"
#include "../include/collisionpixeldata.h"
#include "../include/math.h"
#include "../include/screen.h"
#include <math.h>

CollisionManager* CollisionManager::manager = 0;

const CollisionManager& CollisionManager::Instance()
{
	if (!manager)
		manager = new CollisionManager();

	return *manager;
}

bool CollisionManager::CircleToCircle(double x1, double y1, double r1, double x2, double y2, double r2) const
{
	return SquaredDistance(x1, y1, x2, y2) <= pow(r1 + r2, 2);
}

bool CollisionManager::CircleToPixels(double cx, double cy, double cr, const CollisionPixelData* pixels, double px, double py) const
{
	if (CircleToRect(cx, cy, cr, px, py, pixels->GetWidth(), pixels->GetHeight())) {
		double rx, ry, rw, rh;
        rx = ry = rw = rh = 0;

		OverlappingRect(cx - cr, cy - cr, cr * 2, cr * 2, px, py, pixels->GetWidth(), pixels->GetHeight(), &rx, &ry, &rw, &rh);
        
		uint32 coordXFirstPixel1 = uint32(rx - px);
		uint32 coordYFirstPixel1 = uint32(ry - py);

		for (uint16 i = 0; i < rw; i++)
			for (uint16 j = 0; j < rh; j++)
				if (pixels->GetData(coordXFirstPixel1 + i, coordYFirstPixel1 + j))
					if (SquaredDistance(cx, cy, rx + i, ry + j) <= pow(cr, 2))
						return true;
	}

	return false;
}

bool CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const
{
	double outx, outy;
    outx = outy = 0;

	ClosestPointToRect(cx, cy, rx, ry, rw, rh, &outx, &outy);

	return SquaredDistance(cx, cy, outx, outy) <= pow(cr, 2);
}

bool CollisionManager::PixelsToPixels(const CollisionPixelData* p1, double x1, double y1, const CollisionPixelData* p2, double x2, double y2) const
{
	if (RectToRect(x1, y1, p1->GetWidth(), p2->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight())) {
		double rx, ry, rw, rh;
        rx = ry = rw = rh = 0;

		OverlappingRect(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight(), &rx, &ry, &rw, &rh);

		uint32 coordXFirstPixel1 = uint32(rx - x1);
		uint32 coordYFirstPixel1 = uint32(ry - y1);
		uint32 coordXFirstPixel2 = uint32(rx - x2);
		uint32 coordYFirstPixel2 = uint32(ry - y2);

		for (uint16 i = 0; i < rw; i++)
			for (uint16 j = 0; j < rh; j++)
				if (p1->GetData(coordXFirstPixel1 + i, coordYFirstPixel1 + j) && p2->GetData(coordXFirstPixel2 + i, coordYFirstPixel2 + j))
					return true;
	}

    return false;
}

bool CollisionManager::PixelsToRect(const CollisionPixelData* pixels, double px, double py, double rx, double ry, double rw, double rh) const
{
    if (RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh)){
		double rectx, recty, rectwidth, rectheight;

		OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh, &rectx, &recty, &rectwidth, &rectheight);

		uint32 fromx = uint32(rectx - px);
		uint32 fromy = uint32(recty - py);

		for (uint16 x = 0; x < rectwidth; x++)
			for (uint16 y = 0; y < rectheight; y++)
				if (pixels->GetData(fromx + x, fromy + y))
					return true;
	}
	return false;

}

bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) const
{
    Screen::Instance().SetTitle("X ( " + String::FromInt(w1+h1) + " )( " + String::FromInt(x1) + ", " + String::FromInt(y1) + " ) :: Y ( " + String::FromInt(w2+h2) + " )( " + String::FromInt(x2) + ", " + String::FromInt(y2) + " )");
    if (x2 < 5 && y2 < 5)
        int i = 0;
	return RectsOverlap(x1, y1, w1, h1, x2, y2, w2, h2);
}
