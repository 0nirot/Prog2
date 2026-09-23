#include "TileExit.h"

TileExit::TileExit()
{
	traversable = true;
	startTile = false;
	endTile = true;
	tileVisualization = RED;
}

TileExit::~TileExit()
{
}

bool TileExit::isTraversable() const
{
	return true;
}

bool TileExit::isEndTile() const
{
	return true;
}

Color TileExit::getTileVisualization() const
{
	return tileVisualization;
}
