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

	// Position setzen
	virtual void setPosition(int x, int y) = 0;
};
