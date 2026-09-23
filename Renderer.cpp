#include "Renderer.h"
#include "Map.h"
#include "PlayerCharacter.h"

namespace
{
	const Color BACKGROUND_COLOR = { 30, 30, 36, 255 };
	const Color GRID_COLOR = { 0, 0, 0, 80 };
	const Color PATH_OVERLAY_COLOR = { 0, 200, 80, 90 };
	const Color PLAYER_COLOR = { 41, 128, 255, 255 };
	const Color PLAYER_OUTLINE_COLOR = { 10, 40, 100, 255 };
	const Color STATUS_TEXT_COLOR = RAYWHITE;

	constexpr int STATUS_FONT_SIZE = 20;
	constexpr int TARGET_FPS = 60;
}

Renderer::Renderer(int tileSize, int padding)
	: tileSize(tileSize), padding(padding), statusBarHeight(40), windowOpen(false)
{
}

Renderer::~Renderer()
{
	closeWindow();
}

void Renderer::openWindow(const Map& map, const std::string& title)
{
	if (windowOpen)
		return;

	const int width = map.getWidth() * tileSize + 2 * padding;
	const int height = map.getHeight() * tileSize + 2 * padding + statusBarHeight;

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
	const int barY = map.getHeight() * tileSize + 2 * padding;
	const int textY = barY + (statusBarHeight - STATUS_FONT_SIZE) / 2;

	DrawText(TextFormat("%s  |  Position: (%.1f, %.1f)  |  Carry Weight: %d/%d",
		player.getName().c_str(),
		player.getX(), player.getY(),
		player.getInventory()->getTotalWeight(), player.getMaxCarryWeight()),
		padding, textY, STATUS_FONT_SIZE, STATUS_TEXT_COLOR);
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
