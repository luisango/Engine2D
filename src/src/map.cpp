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

	int offset_x = 0;
    int offset_y = 0;

	if (node_tileset->first_node("tileoffset")) {
		offset_x = atoi(node_tileset->first_node("tileoffset")->first_attribute("x")->value());
		offset_y = atoi(node_tileset->first_node("tileoffset")->first_attribute("y")->value());
	}

    imageFile = String(node_tileset->first_node("image")->first_attribute("source")->value()).StripDir();

	xml_node<>* data_node = node_map->first_node("layer")->first_node("data");

	if (data_node->first_attribute("encoding") || data_node->first_attribute("compression")) 
        return;

	xml_node<>* tile_node = data_node->first_node("tile");
	int first_gid = atoi(node_tileset->first_attribute("firstgid")->value());

	while (tile_node) {
        tileIds.Add(atoi(tile_node->first_attribute("gid")->value()) - first_gid);
		tile_node = tile_node->next_sibling("tile");
	}

    int tileset_tile_width = atoi(node_tileset->first_attribute("tilewidth")->value());
	int tileset_tile_height = atoi(node_tileset->first_attribute("tileheight")->value());
    int image_width = atoi(node_tileset->first_node("image")->first_attribute("width")->value());
	int image_height = atoi(node_tileset->first_node("image")->first_attribute("height")->value());

    image = ResourceManager::Instance().LoadImage(
        filename.ExtractDir() + "/" + imageFile, 
        image_width / tileset_tile_width, 
        image_height / tileset_tile_height
    );

	image->SetHandle(offset_x, offset_y);

	valid = true;
}

void Map::Render() const {
    Renderer::Instance().SetColor(mapr_t, mapg_t, mapb_t, 255);

	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
				Renderer::Instance().DrawImage(image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
			}
		}
	}

    Renderer::Instance().SetColor(255, 255, 255, 255);
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
