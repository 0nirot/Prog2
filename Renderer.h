#pragma once
#include <cstddef>
#include <memory>
#include <string>
#include <raylib.h>
#include "PlayerCharacter.h"

class Map;
class Character;
class ItemBase;
class ItemEquippable;
template<typename T> class ItemContainer;
template<typename T> class EquipmentContainer;

// Kapselt das raylib-Fenster und das Zeichnen der Map als Raster
// aus quadratischen Kacheln, inklusive Spieler, Statuszeile und Inventar.
//
// Layout des Fensters:
//   +-------------------+-------------+
//   |       Map         |  Equipment  |
//   +-------------------+-------------+
//   |     Statusleiste                |
//   +---------------------------------+
//   |     Inventar (Tasche)           |
//   +---------------------------------+
class Renderer
{
public:
	explicit Renderer(int tileSize = 40, int padding = 20);
	~Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	// Öffnet ein Fenster, dessen Größe sich aus den Map-Dimensionen
	// und der Slotanzahl des Spielerinventars ergibt
	void openWindow(const Map& map, const PlayerCharacter& player, const std::string& title);
	void closeWindow();
	bool shouldClose() const;

	// Zeichnet einen kompletten Frame (Map, Spieler, Statuszeile, Inventar)
	void render(const Map& map, const PlayerCharacter& player) const;

	int getTileSize() const;
	int getPadding() const;

private:
	void drawMap(const Map& map) const;
	void drawPlayer(Rectangle playerRect) const;
	void drawStatusBar(const Map& map, const PlayerCharacter& player) const;

	// Zeichnet Tasche (unter der Statusleiste) und Ausrüstung (rechts neben der Map)
	void drawInventory(const Map& map, const PlayerCharacter& player) const;
	// Tasche: eine Zeile pro Slot, Index 0 oben
	void drawBag(int x, int y, const ItemContainer<ItemBase>& bag, const Inventory<ItemBase, ItemEquippable>& inventory) const;
	// Ausrüstung: eine Zeile pro Slot mit Slottyp und Itemname
	void drawEquipment(int x, int y, const EquipmentContainer<ItemEquippable>& equipment) const;
	// Eine Zeile der Tasche: Name, Beschreibung, Gewicht, Wert, Stärkebonus
	void drawItemRow(int x, int y, std::size_t index, const std::shared_ptr<ItemBase>& item, const Inventory<ItemBase, ItemEquippable>& inventory) const;

	Rectangle tileRect(int x, int y) const;

	// Pixelmaße einzelner Bereiche
	int mapPixelWidth(const Map& map) const;
	int mapPixelHeight(const Map& map) const;
	int bagPanelHeight(std::size_t bagSlots) const;
	int bagPanelMinWidth() const;

	int tileSize;
	int padding;
	int statusBarHeight;
	int inventoryRowHeight;
	int inventoryHeaderHeight;
	int equipmentPanelWidth;
	bool windowOpen;
};
