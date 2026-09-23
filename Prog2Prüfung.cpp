// Prog2Prüfung.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Prog2Prüfung.h"
#include "Map.h"
#include "MapGenerator.h"
#include "PlayerCharacter.h"
#include "Renderer.h"
#include <memory>
#include <raylib.h>

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
	}
}

int main()
{
	// Erstelle und generiere die Map
	std::shared_ptr<Map> map = std::make_shared<Map>(15, 15);
	MapGenerator generator;
	generator.generateMap(map);

	// Erstelle Spieler auf dem Start-Tile
	PlayerCharacter player;
	player.setCurrentMap(map);
	player.setPosition(static_cast<int>(map->getStartPosition().x), static_cast<int>(map->getStartPosition().y));

	Renderer renderer(40, 20);
	renderer.openWindow(*map, "Prog2Prüfung - Dungeon");

	while (!renderer.shouldClose()) // Gameloop
	{
		handleInput(player);
		renderer.render(*map, player);
	}

	return 0;
}
