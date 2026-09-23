#pragma once
#include <vector>
#include <memory>
#include "Tile.h"
#include <raylib.h>

class Map
{
public:
	Map(int width, int height);
	~Map();

	void setTile(int x, int y, std::shared_ptr<Tile> tile);
	void setStartPosition(const Vector2& position);
	std::shared_ptr<Tile> getTile(int x, int y) const;

	int getWidth() const;
	int getHeight() const;
	Vector2 getStartPosition() const;

private:
	int mapWidth;
	int mapHeight;
	Vector2 startPosition;
	std::vector<std::vector<std::shared_ptr<Tile>>> mapTiles;
};
