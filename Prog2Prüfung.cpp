// Prog2Prüfung.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Prog2Prüfung.h"
#include "Map.h"
#include "MapGenerator.h"
#include "PlayerCharacter.h"
#include "Renderer.h"
#include <cstdio>
#include <memory>
#include <vector>
#include <raylib.h>
#include "LootTable.h"
#include "PathFinder.h"

namespace
{
	void handleMovementInput(PlayerCharacter& player)
	{
		if (IsKeyPressed(KEY_W))
		{
			player.moveUp();
		}
		if (IsKeyPressed(KEY_S))
		{
			player.moveDown();
		}
		if (IsKeyPressed(KEY_A))
		{
			player.moveLeft();
		}
		if (IsKeyPressed(KEY_D))
		{
			player.moveRight();
		}
		if (IsKeyPressed(KEY_E))
		{
			player.pickUpItem();
		}
		if (IsKeyPressed(KEY_SPACE))
		{
			player.autoWalk();
		}
	}

	// Füllt alle freien Taschenslots mit zufälligen Items aus der LootTable
	void fillInventoryWithRandomItems(PlayerCharacter& player, std::shared_ptr<LootTable> lootTable)
	{
		while (player.getInventory()->addBagItem(lootTable->getRandomItem()) >= 0)
		{
		}
	}

	// Sucht mit A* den kürzesten Weg von der Spielerposition zum Exit und markiert ihn auf der Map
	void showBestPath(Map& map, const PlayerCharacter& player)
	{
		// Alte Markierung entfernen
		for (int y = 0; y < map.getHeight(); ++y)
		{
			for (int x = 0; x < map.getWidth(); ++x)
			{
				if (auto tile = map.getTile(x, y))
					tile->setBestPath(false);
			}
		}

		PathFinder pathFinder;
		std::vector<GridPosition> path = pathFinder.findPathToExit(map, { player.getX(), player.getY() });
		if (path.empty())
		{
			printf("No path from player to exit found\n");
			return;
		}

		for (const GridPosition& position : path)
		{
			map.getTile(position.x, position.y)->setBestPath(true);
		}
		printf("Best path: %d steps\n", static_cast<int>(path.size()) - 1);
	}

	void handleMapInput(Map& map, const PlayerCharacter& player)
	{
		if (IsKeyPressed(KEY_T))
		{
			showBestPath(map, player);
		}
	}

	void handleInvetoryInput(PlayerCharacter& player, std::shared_ptr<LootTable> lootTable)
	{
		if (IsKeyPressed(KEY_UP))
		{
			player.changeInventorySlot(-1);
		}
		if (IsKeyPressed(KEY_DOWN))
		{
			player.changeInventorySlot(1);
		}
		if (IsKeyPressed(KEY_ENTER))
		{
			player.equipItem();
		}
		if (IsKeyPressed(KEY_Q))
		{
			player.dropItem();
		}
		if (IsKeyPressed(KEY_J))
		{
			player.getInventory()->sortBagByWeight();
		}
		if (IsKeyPressed(KEY_K))
		{
			player.getInventory()->sortBagByName();
		}
		if (IsKeyPressed(KEY_L))
		{
			player.getInventory()->sortBagByValue();
		}
		if (IsKeyPressed(KEY_R))
		{
			fillInventoryWithRandomItems(player, lootTable);
		}
	}
}

int main()
{
	// Erstelle und generiere die Map
	std::shared_ptr<Map> map = std::make_shared<Map>(15, 15);
	std::shared_ptr<LootTable> lootTable = std::make_shared<LootTable>();
	MapGenerator generator;
	generator.setLootTable(lootTable);
	generator.generateMap(map);

	// Erstelle Spieler auf dem Start-Tile
	PlayerCharacter player;
	player.setCurrentMap(map);
	player.setPosition(static_cast<int>(map->getStartPosition().x), static_cast<int>(map->getStartPosition().y));

	Renderer renderer(40, 20);
	renderer.openWindow(*map, player, "Prog2Prüfung");

	while (!renderer.shouldClose()) // Gameloop
	{
		// Während autoWalk läuft, keine manuelle Bewegung
		if (!player.isOverWeight() && !player.isAutoWalking())
		{
			handleMovementInput(player);
		}

		// Macht beim automatischen Laufen alle paar Frames einen Schritt
		player.updateAutoWalk(GetFrameTime());

		handleInvetoryInput(player, lootTable);
		handleMapInput(*map, player);
		renderer.render(*map, player);
	}

	return 0;
}
