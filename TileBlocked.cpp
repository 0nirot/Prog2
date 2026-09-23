#include "TileBlocked.h"

TileBlocked::TileBlocked()
{
	traversable = false;
	startTile = false;
	endTile = false;
	tileVisualization = DARKBROWN;
}

TileBlocked::~TileBlocked()
{
}

bool TileBlocked::isTraversable() const
{
	return false;
}

Color TileBlocked::getTileVisualization() const
{
	return tileVisualization;
}
