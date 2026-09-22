#pragma once
#include <vector>
#include <memory>
#include "Tile.h"

class Map
{
public:
	Map(int width, int height);
	~Map();

	void setTile(int x, int y, std::shared_ptr<Tile> tile);
	std::shared_ptr<Tile> getTile(int x, int y) const;

	int getWidth() const;
	int getHeight() const;

private:
	int mapWidth;
	int mapHeight;
	std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles;
};
