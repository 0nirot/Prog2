#include "MapGenerator.h"
#include "TileStart.h"
#include "TileExit.h"
#include "TileTraversable.h"
#include "TileBlocked.h"
#include "TileTreasure.h"
#include "utils.h"
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>
#include "Items\ItemBase.h"

MapGenerator::MapGenerator()
	: startX(0), startY(0), endX(0), endY(0)
{
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::generateMap(std::shared_ptr<Map> map)
{
	startY = 0;
	endY = map->getHeight() - 1;

	startX = utils::trueRand(1, map->getWidth() - 2);
	endX = utils::trueRand(1, map->getWidth() - 2);

	for (int y = 0; y < map->getHeight(); ++y)
	{
		for (int x = 0; x < map->getWidth(); ++x)
		{
			map->setTile(x, y, std::make_shared<TileTraversable>());
		}
	}

	for (int y = 0; y < map->getHeight(); ++y)
	{
		int waypointX = (y == 0) ? startX : (y == endY) ? endX : utils::trueRand(1, map->getWidth() - 2);
		auto waypointTile = map->getTile(waypointX, y);
		if (waypointTile != nullptr)
		{
			waypointTile->setWaypoint(true);
		}
	}

	generatePath(map);

	map->setTile(startX, startY, std::make_shared<TileStart>());
	map->setStartPosition(Vector2{ static_cast<float>(startX), static_cast<float>(startY) });
	map->setTile(endX, endY, std::make_shared<TileExit>());

	fillWithObstacles(map);

	placeTreasures(map);
}

void MapGenerator::generatePath(std::shared_ptr<Map> map)
{
    auto setPath = [&](int x, int y)
        {
            auto tile = std::make_shared<TileTraversable>();
            tile->setPathTile(true);
            map->setTile(x, y, tile);
        };

    std::vector<std::pair<int, int>> waypoints;
    for (int y = startY + 1; y < endY; ++y)
    {
        for (int x = 1; x < map->getWidth() - 1; ++x)
        {
            auto tile = map->getTile(x, y);
            if (tile && tile->isWaypoint())
            {
                waypoints.push_back({ x, y });
                break;
            }
        }
    }
    waypoints.push_back({ endX, endY });

    int x = startX;
    int y = startY;
    int lastHorizontalY = -2;
    setPath(x, y);

    for (auto [wx, wy] : waypoints)
    {
        if (wx != x)
        {
            int minY = std::max(y, lastHorizontalY + 2);
            if (minY > wy)
                minY = wy;

            int turnY = utils::randomRange(minY, wy);

            while (y < turnY)
                setPath(x, ++y);

            int step = (wx > x) ? 1 : -1;
            while (x != wx)
            {
                x += step;
                setPath(x, y);
            }
            lastHorizontalY = y;
        }

        while (y < wy)
            setPath(x, ++y);
    }
}

void MapGenerator::fillWithObstacles(std::shared_ptr<Map> map)
{
	for (int y = 0; y < map->getHeight(); ++y)
	{
		for (int x = 0; x < map->getWidth(); ++x)
		{
			auto tile = map->getTile(x, y);

			if (tile != nullptr && tile->isTraversable() && !tile->isStartTile() && !tile->isEndTile() && !tile->isPathTile())
			{
				if (utils::trueRand(0, 100) < 80)
				{
					map->setTile(x, y, std::make_shared<TileBlocked>());
				}
			}
		}
	}
}

void MapGenerator::placeTreasures(std::shared_ptr<Map> map)
{
	std::shared_ptr<LootTable> currentLootTable = lootTable;
	std::vector<std::pair<int, int>> candidates;
	for (int y = 0; y < map->getHeight(); ++y)
	{
		for (int x = 0; x < map->getWidth(); ++x)
		{
			auto tile = map->getTile(x, y);
			if (tile != nullptr && tile->isPathTile())
				candidates.push_back({ x, y });
		}
	}

	if (candidates.empty())
		return;

	const int treasureCount = std::min(utils::randomRange(5, 10), static_cast<int>(candidates.size()));

	for (int i = 0; i < treasureCount; ++i)
	{
		const int randomIndex = utils::trueRand(0, static_cast<int>(candidates.size()) - 1);
		const auto [x, y] = candidates[randomIndex];

		auto treasureTile = std::make_shared<TileTreasure>();
		int lootTableIndex = utils::trueRand(0, currentLootTable->getItemCount() - 1);
		treasureTile->setLoot(currentLootTable->getItem(lootTableIndex));
		currentLootTable->removeItem(lootTableIndex);
		map->setTile(x, y, treasureTile);

		candidates[randomIndex] = candidates.back();
		candidates.pop_back();
	}
}

void MapGenerator::setLootTable(std::shared_ptr<LootTable> newlootTable)
{
	lootTable = newlootTable;
}
