#pragma once
#include "Map.h"
#include <vector>

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	void generateMap(std::shared_ptr<Map> map);

private:
	void generatePath(std::shared_ptr<Map> map);
	void fillWithObstacles(std::shared_ptr<Map> map);
	void placeTreasures(std::shared_ptr<Map> map);

	int startX;
	int startY;
	int endX;
	int endY;
	std::vector<std::shared_ptr<Tile>> pathTiles;
};
