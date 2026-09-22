#include "Map.h"
#include <algorithm>

Map::Map(int width, int height)
	: mapWidth(std::max(width, 15)), mapHeight(std::max(height, 15)), mapTiles(mapHeight, std::vector<std::shared_ptr<Tile>>(mapWidth, nullptr))
{
}

Map::~Map()
{
	// shared_ptr kümmert sich automatisch um den Speicher
}

void Map::setTile(int x, int y, std::shared_ptr<Tile> tile)
{
	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
	{
		mapTiles[y][x] = tile;
	}
}

std::shared_ptr<Tile> Map::getTile(int x, int y) const
{
	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
	{
		return mapTiles[y][x];
	}
	return nullptr;
}

int Map::getWidth() const
{
	return mapWidth;
}

int Map::getHeight() const
{
	return mapHeight;
}
