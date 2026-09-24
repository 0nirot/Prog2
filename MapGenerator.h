#pragma once
#include "Map.h"
#include <vector>
#include "LootTable.h"

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	void generateMap(std::shared_ptr<Map> map);
	void setLootTable(std::shared_ptr<LootTable> newlootTable);

private:
	void generatePath(std::shared_ptr<Map> map);
	void fillWithObstacles(std::shared_ptr<Map> map);
	void placeTreasures(std::shared_ptr<Map> map);

	int startX;
	int startY;
	int endX;
	int endY;
	std::shared_ptr<LootTable> lootTable;
};
