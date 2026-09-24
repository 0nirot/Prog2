#include "Tile.h"

Tile::Tile()
	: traversable(false), startTile(false), endTile(false), playerOnTile(false), isPath(false), waypoint(false), bestPath(false), tileVisualization(DARKGRAY)
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
}

void Tile::setPlayerOnTile(bool player)
{
	if (player)
	{
		traverse();
	}
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

bool Tile::isBestPath() const
{
	return bestPath;
}

void Tile::setBestPath(bool bestPath_)
{
	bestPath = bestPath_;
}
