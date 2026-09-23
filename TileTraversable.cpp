#include "TileTraversable.h"

TileTraversable::TileTraversable()
{
	traversable = true;
	startTile = false;
	endTile = false;
	tileVisualization = 'N';
}

TileTraversable::~TileTraversable()
{
}

bool TileTraversable::isTraversable() const
{
	return true;
}

char TileTraversable::getTileVisualization() const
{
	return tileVisualization;
}
