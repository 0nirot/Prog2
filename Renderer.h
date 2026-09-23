#pragma once
#include <string>
#include <raylib.h>

class Map;
class Character;

// Kapselt das raylib-Fenster und das Zeichnen der Map als Raster
// aus quadratischen Kacheln, inklusive Spieler und Statuszeile.
class Renderer
{
public:
	explicit Renderer(int tileSize = 40, int padding = 20);
	~Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	// Öffnet ein Fenster, dessen Größe sich aus den Map-Dimensionen ergibt
	void openWindow(const Map& map, const std::string& title);
	void closeWindow();
	bool shouldClose() const;

	// Zeichnet einen kompletten Frame (Map, Spieler, Statuszeile)
	void render(const Map& map, const Character& player) const;

	int getTileSize() const;
	int getPadding() const;

private:
	void drawMap(const Map& map) const;
	void drawPlayer(Rectangle playerRect) const;
	void drawStatusBar(const Map& map, const Character& player) const;

	Rectangle tileRect(int x, int y) const;

	int tileSize;
	int padding;
	int statusBarHeight;
	bool windowOpen;
};
