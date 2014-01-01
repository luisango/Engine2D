#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/collision.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

Map::Map(const String &filename, uint16 firstColId) {
    this->filename = filename;
    this->firstColId = firstColId;

    String content = String::Read(filename);

    xml_document<> doc;
    doc.parse<0>((char*) content.ToCString());

    // Get elements
    xml_node<>* node_map = doc.first_node("map");
    
    // Get attributes
    width      = atoi(node_map->first_attribute("width")->value());
	height     = atoi(node_map->first_attribute("height")->value());
	tileWidth  = atoi(node_map->first_attribute("tilewidth")->value());
	tileHeight = atoi(node_map->first_attribute("tileheight")->value());

    xml_node<>* node_tileset = node_map->first_node("tileset");

	int firstGid = atoi(node_tileset->first_attribute("firstgid")->value());
	uint16 tilesetTileWidth = atoi(node_tileset->first_attribute("tilewidth")->value());
	uint16 tilesetTileHeight = atoi(node_tileset->first_attribute("tileheight")->value());

	int offsetX = 0, offsetY = 0;
	if ( node_tileset->first_node("tileoffset") ) {
		offsetX = atoi(node_tileset->first_node("tileoffset")->first_attribute("x")->value());
		offsetY = atoi(node_tileset->first_node("tileoffset")->first_attribute("y")->value());
	}

    imageFile = String(node_tileset->first_node("image")->first_attribute("source")->value()).StripDir();

	int imageWidth = atoi(node_tileset->first_node("image")->first_attribute("width")->value());
	int imageHeight = atoi(node_tileset->first_node("image")->first_attribute("height")->value());

	// Leemos el primer layer, sin codificacion ni compresion (los demas son ignorados)
	xml_node<>* dataNode = node_map->first_node("layer")->first_node("data");
	if ( dataNode->first_attribute("encoding") || dataNode->first_attribute("compression") ) return;
	xml_node<>* tileNode = dataNode->first_node("tile");
	while ( tileNode ) {
        tileIds.Add(atoi(tileNode->first_attribute("gid")->value()) - firstGid);
		tileNode = tileNode->next_sibling("tile");
	}

	// Cargamos la imagen
    image = ResourceManager::Instance().LoadImage(filename.ExtractDir() + "/" + imageFile, imageWidth/tilesetTileWidth, imageHeight/tilesetTileHeight);
	image->SetHandle(offsetX, offsetY);

	valid = true;
}

void Map::Render() const {
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
				Renderer::Instance().DrawImage(image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
			}
		}
	}
}

bool Map::CheckCollision(const Collision* collision) const {
	// Creamos caja de colisiones
	double boxX = 0, boxY = 0, boxWidth = GetTileWidth(), boxHeight = GetTileHeight();
	RectCollision boxCol(&boxX, &boxY, &boxWidth, &boxHeight);
	
	// Comprobamos colision con cada tile
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= firstColId ) {
				boxX = x * GetTileWidth();
				boxY = y * GetTileHeight();

				if ( collision->DoesCollide(&boxCol) )
					return true;
			}
		}
	}

	return false;
}

double Map::GetGroundY(double x, double y) const {
	double groundY = UINT_MAX;

	if ( x < 0  ||  x >= width*tileWidth  ||  y >= height*tileHeight ) return groundY;
	if ( y < 0 ) y = 0;

	// Buscamos el primer tile en esa columna
	for ( int tiley = int(y/tileHeight); tiley < height; tiley++ ) {
		if ( tileIds[tiley*width + int(x/tileWidth)] >= 0 ) {
			groundY = tiley*tileHeight;
			break;
		}
	}
	return groundY;
}
