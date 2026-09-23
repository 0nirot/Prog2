#include "MapGenerator.h"
#include "TileStart.h"
#include "TileExit.h"
#include "TileTraversable.h"
#include "TileBlocked.h"
#include "TileTreasure.h"
#include "utils.h"
#include <memory>
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
	pathTiles.clear();  // Leere den Vector für neue Karte

	// Start und End X an zufälligen Positionen in ihrer Reihe
	startX = utils::trueRand(1, map->getWidth() - 2);
	endX = utils::trueRand(1, map->getWidth() - 2);

	// Zunächst alles mit passierbar füllen
	for (int y = 0; y < map->getHeight(); ++y)
	{
		for (int x = 0; x < map->getWidth(); ++x)
		{
			map->setTile(x, y, std::make_shared<TileTraversable>());
		}
	}

	// Setze Waypoints für jede Reihe
	for (int y = 0; y < map->getHeight(); ++y)
	{
		int waypointX = (y == 0) ? startX : (y == endY) ? endX : utils::trueRand(1, map->getWidth() - 2);
		auto waypointTile = map->getTile(waypointX, y);
		if (waypointTile != nullptr)
		{
			waypointTile->setWaypoint(true);
		}
	}

	// Pfad vom Start zum Ende erzeugen
	generatePath(map);
	//generatePath(map);

	// Start und Ende setzen
	map->setTile(startX, startY, std::make_shared<TileStart>());
	map->setStartPosition(Vector2{ static_cast<float>(startX), static_cast<float>(startY) });
	map->setTile(endX, endY, std::make_shared<TileExit>());

	// Zufällige Hindernisse hinzufügen
	fillWithObstacles(map);

	// Schätze hinzufügen
	placeTreasures(map);
}

void MapGenerator::generatePath(std::shared_ptr<Map> map)
{
    auto setPath = [&](int x, int y)
        {
            auto tile = std::make_shared<TileTraversable>();
            tile->setPathTile(true);
            map->setTile(x, y, tile);
            pathTiles.push_back(tile);  // Speichere shared_ptr auf das Tile in den Vector
        };

    // Waypoints von oben nach unten sammeln, Ziel als letzter Waypoint
    std::vector<std::pair<int, int>> waypoints;
    for (int y = startY + 1; y < endY; ++y)
    {
        for (int x = 1; x < map->getWidth() - 1; ++x)
        {
            auto tile = map->getTile(x, y);
            if (tile && tile->isWaypoint())
            {
                waypoints.push_back({ x, y });
                break; // max. ein Waypoint pro Reihe
            }
        }
    }
    waypoints.push_back({ endX, endY });

    int x = startX;
    int y = startY;
    int lastHorizontalY = -2; // Reihe des letzten horizontalen Segments
    setPath(x, y);

    for (auto [wx, wy] : waypoints)
    {
        if (wx != x)
        {
            // Frühestmögliche Reihe: eine Reihe Abstand zum letzten horizontalen Segment
            int minY = std::max(y, lastHorizontalY + 2);
            if (minY > wy)
                minY = wy; // Waypoint erzwingt es, dann darf es direkt darunter liegen

            int turnY = utils::randomRange(minY, wy);

            // Runter bis zur Abbiege-Reihe
            while (y < turnY)
                setPath(x, ++y);

            // Horizontal zum Waypoint-X
            int step = (wx > x) ? 1 : -1;
            while (x != wx)
            {
                x += step;
                setPath(x, y);
            }
            lastHorizontalY = y;
        }

        // Rest runter bis zum Waypoint
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
	// Wenn nicht genug Path-Tiles existieren, beende die Methode
	if (pathTiles.empty())
		return;

	// Anzahl der Schätze zwischen 5-10
	int treasureCount = utils::randomRange(5, 10);

	// Begrenzen auf verfügbare Path-Tiles
	if (treasureCount > static_cast<int>(pathTiles.size()))
		treasureCount = pathTiles.size();

	// Platziere Schätze auf zufälligen Indizes des pathTiles Vectors
	for (int i = 0; i < treasureCount; ++i)
	{
		// Wähle zufälligen Index aus pathTiles
		int randomIndex = utils::trueRand(0, static_cast<int>(pathTiles.size()) - 1);
		auto treasureTile = std::make_shared<TileTreasure>();

		// Finde die Koordinaten des Tiles in der Map
		for (int y = 0; y < map->getHeight(); ++y)
		{
			for (int x = 0; x < map->getWidth(); ++x)
			{
				auto currentTile = map->getTile(x, y);
				// Vergleiche mit dem Tile aus pathTiles
				if (currentTile == pathTiles[randomIndex])
				{
					// Ersetze TileTraversable mit TileTreasure
					map->setTile(x, y, treasureTile);
					treasureTile->setLoot(lootTable->getRandomItem());
					// Entferne das Tile aus dem Vector um Duplikate zu vermeiden
					pathTiles.erase(pathTiles.begin() + randomIndex);
					goto next_treasure;
				}
			}
		}
		next_treasure:;
	}
}

void MapGenerator::setLootTable(std::shared_ptr<LootTable> newlootTable)
{
	lootTable = newlootTable;
}
