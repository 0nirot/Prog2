#include "TileExit.h"

TileExit::TileExit()
{
	traversable = true;
	startTile = false;
	endTile = true;
	tileVisualization = 'E';
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

char TileExit::getTileVisualization() const
{
	return tileVisualization;
}
