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
	void handleInput(PlayerCharacter& player)
	{
		if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
		{
			player.moveUp();
		}
		if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
		{
			player.moveDown();
		}
		if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
		{
			player.moveLeft();
		}
		if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
		{
			player.moveRight();
		}
		if (IsKeyPressed(KEY_E))
		{
			player.pickUpItem();
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
	renderer.openWindow(*map, "Prog2Prüfung");

	while (!renderer.shouldClose()) // Gameloop
	{
		if (!player.isOverWeight())
		{
			handleInput(player);
		}
		renderer.render(*map, player);
	}

	return 0;
}
