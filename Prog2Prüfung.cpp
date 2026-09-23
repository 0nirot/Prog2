#include "Prog2Prüfung.h"
#include "Map.h"
#include "MapGenerator.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include "Inventory.h"
#include "ItemSword.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "ItemTrinket.h"
#include "EquipmentContainer.h"
#include "PlayerCharacter.h"
#include <raylib.h>

using namespace std;

// Plattformunabhängige Deklaration; die Windows-spezifische Implementierung
// befindet sich in WindowsConsole.cpp, damit <windows.h> nicht in dieser TU
// mit anderen Bibliotheken (z.B. raylib) kollidiert.
void enableAnsiEscapes();

void renderMap(const std::shared_ptr<Map>& map)
{
	ostringstream frame;

	frame << "\033[H"; // Cursor nach oben links

	for (int y = 0; y < map->getHeight(); ++y)
	{
		for (int x = 0; x < map->getWidth(); ++x)
		{
			auto tile = map->getTile(x, y);
			if (tile != nullptr)
			{
				// Wenn Spieler auf diesem Tile ist, @ zeichnen
				if (tile->isPlayerOnTile())
				{
					frame << "@";
				}
				// Wenn Pfad, dann grün färben
				else if (tile->isPathTile())
				{
					frame << "\033[32m" << tile->getTileVisualization() << "\033[0m";
				}
				else
				{
					frame << tile->getTileVisualization();
				}
			}

		}
		frame << "\033[K\n"; // Rest der Zeile löschen
	}

	cout << frame.str() << flush;
}

int main()
{
	enableAnsiEscapes();

	// Erstelle eine Map
	std::shared_ptr<Map> map = std::make_shared<Map>(15, 15);

	// Generiere die Map
	MapGenerator generator;
	generator.generateMap(map);

	//Erstelle player
	PlayerCharacter player;
	player.setCurrentMap(map);
	player.setPosition(static_cast<int>(map->getStartPosition().x), static_cast<int>(map->getStartPosition().y));


	std::cout << "\033[2J"; // Bildschirm einmalig komplett leeren

	while (true) //gameloop
	{
		renderMap(map);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (IsKeyPressed(KEY_UP))
		{
			player.moveUp();
		}
		if (IsKeyPressed(KEY_DOWN))
		{
			player.moveDown();
		}
		if (IsKeyPressed(KEY_LEFT))
		{
			player.moveLeft();
		}
		if (IsKeyPressed(KEY_RIGHT))
		{
			player.moveRight();
		}
		printf("Player position: (%d, %d)\n", player.getX(), player.getY());
	}

	return 0;
}