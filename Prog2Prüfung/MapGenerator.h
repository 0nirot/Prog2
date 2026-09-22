#pragma once
#include "Map.h"
#include <vector>

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	void generateMap(Map& map);

private:
	void generatePath(Map& map);
	void fillWithObstacles(Map& map);
	void placeTreasures(Map& map);

	int startX;
	int startY;
	int endX;
	int endY;
	std::vector<std::shared_ptr<Tile>> pathTiles;
};
