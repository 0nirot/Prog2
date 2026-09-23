#include "TileBlocked.h"

TileBlocked::TileBlocked()
{
	traversable = false;
	startTile = false;
	endTile = false;
	tileVisualization = '#';
}

TileBlocked::~TileBlocked()
{
}

bool TileBlocked::isTraversable() const
{
	return false;
}

char TileBlocked::getTileVisualization() const
{
	return tileVisualization;
}
