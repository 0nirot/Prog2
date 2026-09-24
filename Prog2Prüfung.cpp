// Prog2Prüfung.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Prog2Prüfung.h"
#include "Map.h"
#include "MapGenerator.h"
#include "PlayerCharacter.h"
#include "Renderer.h"
#include <memory>
#include <raylib.h>
#include "LootTable.h"

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
		if (IsKeyPressed(KEY_ENTER))
		{
			player.equipItem();
		}
	}

	void handleInvetoryInput(PlayerCharacter& player)
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
		if (!player.isOverWeight())
		{
			handleMovementInput(player);
		}

		handleInvetoryInput(player);
		renderer.render(*map, player);
	}

	return 0;
}
