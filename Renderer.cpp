#include "Renderer.h"
#include "Map.h"
#include "PlayerCharacter.h"
#include "Inventory.h"
#include "ItemContainer.h"
#include "EquipmentContainer.h"
#include "Items\ItemBase.h"
#include "Items\ItemEquippable.h"

#include <algorithm>

namespace
{
	const Color BACKGROUND_COLOR = { 30, 30, 36, 255 };
	const Color GRID_COLOR = { 0, 0, 0, 80 };
	const Color PATH_OVERLAY_COLOR = { 0, 200, 80, 90 };
	const Color BEST_PATH_COLOR = { 0, 90, 255, 150 }; // halbtransparentes Blau
	const Color PLAYER_COLOR = { 41, 128, 255, 255 };
	const Color PLAYER_OUTLINE_COLOR = { 10, 40, 100, 255 };
	const Color STATUS_TEXT_COLOR = RAYWHITE;

	// Inventar
	const Color PANEL_COLOR = { 40, 40, 48, 255 };
	const Color PANEL_BORDER_COLOR = { 90, 90, 100, 255 };
	const Color ROW_ALT_COLOR = { 48, 48, 58, 255 };
	const Color HEADER_TEXT_COLOR = { 200, 200, 210, 255 };
	const Color ITEM_TEXT_COLOR = RAYWHITE;
	const Color EMPTY_SLOT_TEXT_COLOR = { 120, 120, 130, 255 };

	constexpr int STATUS_FONT_SIZE = 20;
	constexpr int INVENTORY_FONT_SIZE = 16;
	constexpr int TARGET_FPS = 60;

	// Spaltenoffsets (relativ zum linken Rand des Taschen-Panels) für die Item-Zeilen
	constexpr int COL_INDEX = 8;
	constexpr int COL_NAME = 40;
	constexpr int COL_DESCRIPTION = 180;
	constexpr int COL_WEIGHT = 470;
	constexpr int COL_VALUE = 550;
	constexpr int COL_STRENGTH = 620;
	constexpr int COL_END = 690;
}

Renderer::Renderer(int tileSize, int padding)
	: tileSize(tileSize)
	, padding(padding)
	, statusBarHeight(40)
	, inventoryRowHeight(24)
	, inventoryHeaderHeight(28)
	, equipmentPanelWidth(240)
	, windowOpen(false)
{
}

Renderer::~Renderer()
{
	closeWindow();
}

void Renderer::openWindow(const Map& map, const PlayerCharacter& player, const std::string& title)
{
	if (windowOpen)
		return;

	const auto& inventory = *player.getInventory();

	// Breite: Map + Equipment-Panel rechts daneben, mindestens aber so breit wie das Taschen-Panel
	const int mapAndEquipmentWidth = padding + mapPixelWidth(map) + padding + equipmentPanelWidth + padding;
	const int width = std::max(mapAndEquipmentWidth, padding + bagPanelMinWidth() + padding);

	// Höhe: Map, Statusleiste und darunter das Taschen-Panel
	const int height = padding + mapPixelHeight(map) + padding
		+ statusBarHeight
		+ bagPanelHeight(inventory.getBag().getSlotCount()) + padding;

	InitWindow(width, height, title.c_str());
	SetTargetFPS(TARGET_FPS);
	windowOpen = true;
}

void Renderer::closeWindow()
{
	if (!windowOpen)
		return;

	CloseWindow();
	windowOpen = false;
}

bool Renderer::shouldClose() const
{
	return !windowOpen || WindowShouldClose();
}

void Renderer::render(const Map& map, const PlayerCharacter& player) const
{
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);

	drawMap(map);
	drawStatusBar(map, player);
	drawInventory(map, player);

	EndDrawing();
}

int Renderer::getTileSize() const
{
	return tileSize;
}

int Renderer::getPadding() const
{
	return padding;
}

void Renderer::drawMap(const Map& map) const
{
	for (int y = 0; y < map.getHeight(); ++y)
	{
		for (int x = 0; x < map.getWidth(); ++x)
		{
			auto tile = map.getTile(x, y);
			if (tile == nullptr)
				continue;

			const Rectangle rect = tileRect(x, y);

			DrawRectangleRec(rect, tile->getTileVisualization());

			/*
			// Pfad-Tiles bekommen ein halbtransparentes Overlay,
			// damit Start/Ende/Schätze ihre eigene Farbe behalten
			if (tile->isPathTile())
			{
				DrawRectangleRec(rect, PATH_OVERLAY_COLOR);
			}
			*/

			// Kürzester Weg (Taste T): blaues Overlay, Start/Exit bleiben erkennbar
			if (tile->isBestPath())
			{
				DrawRectangleRec(rect, BEST_PATH_COLOR);
			}

			if (tile->isPlayerOnTile())
			{
				drawPlayer(rect);
			}
			DrawRectangleLinesEx(rect, 1.0f, GRID_COLOR);
		}
	}
}

void Renderer::drawPlayer(Rectangle playerRect) const
{
	const Rectangle rect = playerRect;
	const Vector2 center = { rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f };
	const float radius = tileSize * 0.35f;

	DrawCircleV(center, radius, PLAYER_COLOR);
	DrawCircleLinesV(center, radius, PLAYER_OUTLINE_COLOR);
}

void Renderer::drawStatusBar(const Map& map, const PlayerCharacter& player) const
{
	const int barY = padding + mapPixelHeight(map) + padding;
	const int textY = barY + (statusBarHeight - STATUS_FONT_SIZE) / 2;

	DrawText(TextFormat("%s  |  Position: (%d, %d)  |  Carry Weight: %.1f/%.1f",
		player.getName().c_str(),
		player.getX(), player.getY(),
		player.getInventory()->getTotalWeight(), player.getMaxCarryWeight()),
		padding, textY, STATUS_FONT_SIZE, STATUS_TEXT_COLOR);
}

void Renderer::drawInventory(const Map& map, const PlayerCharacter& player) const
{
	const auto& inventory = *player.getInventory();

	// Ausrüstung: rechts neben der Map, oben ausgerichtet
	const int equipmentX = padding + mapPixelWidth(map) + padding;
	const int equipmentY = padding;
	drawEquipment(equipmentX, equipmentY, inventory.getEquipment());

	// Tasche: unter der Statusleiste
	const int bagX = padding;
	const int bagY = padding + mapPixelHeight(map) + padding + statusBarHeight;
	drawBag(bagX, bagY, inventory.getBag(), inventory);
}

void Renderer::drawBag(int x, int y, const ItemContainer<ItemBase>& bag, const Inventory<ItemBase, ItemEquippable>& inventory) const
{
	const std::size_t slotCount = bag.getSlotCount();
	const int panelWidth = std::max(bagPanelMinWidth(), GetScreenWidth() - 2 * padding);
	const int panelHeight = bagPanelHeight(slotCount);

	// Panel-Hintergrund
	DrawRectangle(x, y, panelWidth, panelHeight, PANEL_COLOR);
	DrawRectangleLines(x, y, panelWidth, panelHeight, PANEL_BORDER_COLOR);

	// Kopfzeile
	const int headerTextY = y + (inventoryHeaderHeight - INVENTORY_FONT_SIZE) / 2;
	DrawText("#", x + COL_INDEX, headerTextY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);
	DrawText("Name", x + COL_NAME, headerTextY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);
	DrawText("Description", x + COL_DESCRIPTION, headerTextY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);
	DrawText("Weight", x + COL_WEIGHT, headerTextY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);
	DrawText("Value", x + COL_VALUE, headerTextY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);
	DrawText("Strength", x + COL_STRENGTH, headerTextY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);
	DrawLine(x, y + inventoryHeaderHeight, x + panelWidth, y + inventoryHeaderHeight, PANEL_BORDER_COLOR);

	// Zeilen in Array-Reihenfolge: Index 0 direkt unter der Kopfzeile
	for (std::size_t i = 0; i < slotCount; ++i)
	{
		const int rowY = y + inventoryHeaderHeight + static_cast<int>(i) * inventoryRowHeight;

		if (i % 2 == 1)
		{
			DrawRectangle(x, rowY, panelWidth, inventoryRowHeight, ROW_ALT_COLOR);
		}

		drawItemRow(x, rowY, i, bag.getItem(i), inventory);
	}

}

void Renderer::drawItemRow(int x, int y, std::size_t index, const std::shared_ptr<ItemBase>& item, const Inventory<ItemBase, ItemEquippable>& inventory) const
{
	const int textY = y + (inventoryRowHeight - INVENTORY_FONT_SIZE) / 2;

	DrawText(TextFormat("%d", static_cast<int>(index) +1), x + COL_INDEX, textY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);

	if (!item)
	{
		if (index == inventory.getSelectedSlotIndex())
		{
			DrawText("> - empty -", x + COL_NAME, textY, INVENTORY_FONT_SIZE, EMPTY_SLOT_TEXT_COLOR);
		}
		else
		{
			DrawText("- empty -", x + COL_NAME, textY, INVENTORY_FONT_SIZE, EMPTY_SLOT_TEXT_COLOR);
		}
		return;
	}

	if (index == inventory.getSelectedSlotIndex())
	{
		DrawText(TextFormat("> %s", item->getName().c_str()), x + COL_NAME, textY, INVENTORY_FONT_SIZE, ITEM_TEXT_COLOR);
	}
	else
	{
		DrawText(item->getName().c_str(), x + COL_NAME, textY, INVENTORY_FONT_SIZE, ITEM_TEXT_COLOR);
	}
	DrawText(item->getDescription().c_str(), x + COL_DESCRIPTION, textY, INVENTORY_FONT_SIZE, ITEM_TEXT_COLOR);
	DrawText(TextFormat("%.1f", item->getWeight()), x + COL_WEIGHT, textY, INVENTORY_FONT_SIZE, ITEM_TEXT_COLOR);
	DrawText(TextFormat("%d", item->getValue()), x + COL_VALUE, textY, INVENTORY_FONT_SIZE, ITEM_TEXT_COLOR);

	// Stärkebonus gibt es nur bei ausrüstbaren Items
	if (auto equippable = std::dynamic_pointer_cast<ItemEquippable>(item))
	{
		DrawText(TextFormat("%+.1f", equippable->getStrengthBonus()), x + COL_STRENGTH, textY, INVENTORY_FONT_SIZE, ITEM_TEXT_COLOR);
	}
	else
	{
		DrawText("-", x + COL_STRENGTH, textY, INVENTORY_FONT_SIZE, EMPTY_SLOT_TEXT_COLOR);
	}
}

void Renderer::drawEquipment(int x, int y, const EquipmentContainer<ItemEquippable>& equipment) const
{
	const std::size_t slotCount = equipment.getSlotCount();
	const int panelHeight = inventoryHeaderHeight + static_cast<int>(slotCount) * inventoryRowHeight;

	// Panel-Hintergrund
	DrawRectangle(x, y, equipmentPanelWidth, panelHeight, PANEL_COLOR);
	DrawRectangleLines(x, y, equipmentPanelWidth, panelHeight, PANEL_BORDER_COLOR);

	// Kopfzeile
	const int headerTextY = y + (inventoryHeaderHeight - INVENTORY_FONT_SIZE) / 2;
	DrawText("Equipment", x + COL_INDEX, headerTextY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);
	DrawLine(x, y + inventoryHeaderHeight, x + equipmentPanelWidth, y + inventoryHeaderHeight, PANEL_BORDER_COLOR);

	// Slots in Array-Reihenfolge: "Slottyp: Itemname"
	for (std::size_t i = 0; i < slotCount; ++i)
	{
		const int rowY = y + inventoryHeaderHeight + static_cast<int>(i) * inventoryRowHeight;
		const int textY = rowY + (inventoryRowHeight - INVENTORY_FONT_SIZE) / 2;

		if (i % 2 == 1)
		{
			DrawRectangle(x, rowY, equipmentPanelWidth, inventoryRowHeight, ROW_ALT_COLOR);
		}

		DrawText(TextFormat("%s:", equipment.getSlotTypeName(i)), x + COL_INDEX, textY, INVENTORY_FONT_SIZE, HEADER_TEXT_COLOR);

		auto item = equipment.getItem(i);
		const int itemX = x + equipmentPanelWidth / 3;
		if (item)
		{
			DrawText(item->getName().c_str(), itemX, textY, INVENTORY_FONT_SIZE, ITEM_TEXT_COLOR);
		}
		else
		{
			DrawText("- empty -", itemX, textY, INVENTORY_FONT_SIZE, EMPTY_SLOT_TEXT_COLOR);
		}
	}
}

Rectangle Renderer::tileRect(int x, int y) const
{
	return Rectangle{
		static_cast<float>(padding + x * tileSize),
		static_cast<float>(padding + y * tileSize),
		static_cast<float>(tileSize),
		static_cast<float>(tileSize)
	};
}

int Renderer::mapPixelWidth(const Map& map) const
{
	return map.getWidth() * tileSize;
}

int Renderer::mapPixelHeight(const Map& map) const
{
	return map.getHeight() * tileSize;
}

int Renderer::bagPanelHeight(std::size_t bagSlots) const
{
	return inventoryHeaderHeight + static_cast<int>(bagSlots) * inventoryRowHeight;
}

int Renderer::bagPanelMinWidth() const
{
	return COL_END;
}
