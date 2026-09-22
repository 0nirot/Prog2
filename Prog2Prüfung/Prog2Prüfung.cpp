// Prog2Prüfung.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

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

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Aktiviert ANSI-Escapes in der Windows-Konsole (unter Linux/macOS nicht nötig)
void enableAnsiEscapes()
{
#ifdef _WIN32
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	if (GetConsoleMode(hOut, &mode))
		SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void renderMap(const Map& map)
{
	ostringstream frame;

	frame << "\033[H"; // Cursor nach oben links

	for (int y = 0; y < map.getHeight(); ++y)
	{
		for (int x = 0; x < map.getWidth(); ++x)
		{
			auto tile = map.getTile(x, y);
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

	// Definiere das Equipment-Layout mit SlotTypes
	std::vector<SlotType<ItemEquippable>> equipmentLayout = {
		makeSlotType<ItemWeapon>("Waffe"),
		makeSlotType<ItemArmor>("Rüstung"),
		makeSlotType<ItemTrinket>("Schmuck")
	};

	Inventory<ItemBase, ItemEquippable> inventory(10, equipmentLayout);

	// Füge Items zur Tasche hinzu
	inventory.addBagItem(std::make_shared<ItemBase>("Potion", "Heals 50 HP", 0.5f, 10));
	inventory.addBagItem(std::make_shared<ItemWeapon>());
	inventory.addBagItem(std::make_shared<ItemArmor>());
	inventory.addBagItem(std::make_shared<ItemTrinket>());

	std::cout << "Tasche hat Item an Index: " << inventory.getBagItem(0)->getName() << std::endl;

	// Erstelle eine Map
	Map map(15, 15);

	// Generiere die Map
	MapGenerator generator;
	generator.generateMap(map);

	std::cout << "\033[2J"; // Bildschirm einmalig komplett leeren

	while (true) //gameloop
	{
		renderMap(map);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}