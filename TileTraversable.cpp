#include "TileTraversable.h"

TileTraversable::TileTraversable()
{
	traversable = true;
	startTile = false;
	endTile = false;
	tileVisualization = LIGHTGRAY;
}

TileTraversable::~TileTraversable()
{
}

bool TileTraversable::isTraversable() const
{
	return true;
}

Color TileTraversable::getTileVisualization() const
{
	return tileVisualization;
}
