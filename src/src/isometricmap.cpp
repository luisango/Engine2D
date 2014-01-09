#include "../include/isometricmap.h"
#include "../include/isometricscene.h"
#include "../include/isometricsprite.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../lib/rapidxml.hpp"

using namespace rapidxml;

IsometricMap::IsometricMap(const String& filename, uint16 firstColId) : Map(filename, firstColId) {
    String content = String::Read(filename);

    // Parse XML
    xml_document<> doc;
    doc.parse<0>((char*) content.ToCString());

    // Get elements of the XML
    xml_node<>* node_map = doc.first_node("map");
    xml_node<>* node_tileset = node_map->first_node("tileset");
    xml_node<>* data_node = node_map->first_node("layer")->next_sibling()->first_node("data");
	xml_node<>* tile_node = data_node->first_node("tile");
    
    // Process tiles
	int first_gid = atoi(node_tileset->first_attribute("firstgid")->value());

	while (tile_node) {
        topLayerIds.Add(atoi(tile_node->first_attribute("gid")->value()) - first_gid);
		tile_node = tile_node->next_sibling("tile");
	}

    // Adjust handle
    Image* img = GetImage();
    img->SetHandle(
        img->GetHandleX() + GetTileWidth(),
        img->GetHeight() - img->GetHandleY() - GetTileHeight()
    );
}

void IsometricMap::GenerateLayerSprites(IsometricScene* scene) {
    for (uint16 y = 0; y < GetRows(); y++) 
		for (uint16 x = 0; x < GetColumns(); x++) 
			if (topLayerIds[y * GetColumns() + x] > -1) {

                IsometricSprite* sprite = scene->CreateSprite(GetImage());

				if (topLayerIds[y*GetColumns() + x] >= GetFirstColId())
					sprite->SetCollision(Sprite::COLLISION_RECT);
                
				sprite->SetPosition(x * GetTileWidth(), y * GetTileHeight());

				sprite->SetCurrentFrame(topLayerIds[y * GetColumns() + x]);
            }
}

void IsometricMap::Render() const {
    double screenX, screenY;

    for (uint16 y = 0; y < GetRows(); y++) {
		for (uint16 x = 0; x < GetColumns(); x++) {
			if (GetTileId(x, y) >= 0) {
                TransformIsoCoords(x * GetTileWidth(), y * GetTileHeight(), 0, &screenX, &screenY);
                Renderer::Instance().DrawImage(GetImage(), screenX, screenY, GetTileId(x, y));
			}
		}
	}

    Renderer::Instance().SetColor(255, 255, 255, 255);
}
