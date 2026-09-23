#pragma once
#include "Map.h"
// Interface-Klasse für Bewegung (abstrakte Basisklasse)
class Movement
{
public:
	virtual ~Movement() = default;

	// Bewegung nach oben
	virtual void moveUp() = 0;

	// Bewegung nach unten
	virtual void moveDown() = 0;

	// Bewegung nach links
	virtual void moveLeft() = 0;

	// Bewegung nach rechts
	virtual void moveRight() = 0;

	// Aktuelle Position abrufen
	virtual int getX() const = 0;
	virtual int getY() const = 0;

	bool isMovePossible(int newX, int newY, const Map& map) const
	{
		// Überprüfen, ob die neue Position innerhalb der Grenzen der Karte liegt
		if (newX < 0 || newX >= map.getWidth() || newY < 0 || newY >= map.getHeight())
			return false;
		// Überprüfen, ob das Tile an der neuen Position begehbar ist
		auto tile = map.getTile(newX, newY);
		if (tile == nullptr || !tile->isTraversable())
			return false;
		return true;
	}

	// Position setzen
	virtual void setPosition(int x, int y) = 0;
};
