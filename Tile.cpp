#include "Tile.h"

Tile::Tile()
	: traversable(false), startTile(false), endTile(false), playerOnTile(false), isPath(false), waypoint(false), tileVisualization(DARKGRAY)
{
}

Tile::~Tile()
{
}

bool Tile::isTraversable() const
{
	return traversable;
}

bool Tile::isStartTile() const
{
	return startTile;
}

bool Tile::isEndTile() const
{
	return endTile;
}

bool Tile::isPlayerOnTile() const
{
	return playerOnTile;
}

Color Tile::getTileVisualization() const
{
	return tileVisualization;
}

void Tile::traverse()
{
	// Standard-Implementierung (kann von Child-Klassen überschrieben werden)
}

void Tile::setPlayerOnTile(bool player)
{
	playerOnTile = player;
}

bool Tile::isPathTile() const
{
	return isPath;
}

void Tile::setPathTile(bool isPath_)
{
	isPath = isPath_;
}

bool Tile::isWaypoint() const
{
	return waypoint;
}

void Tile::setWaypoint(bool waypoint_)
{
	waypoint = waypoint_;
}
