#include "TileStart.h"

TileStart::TileStart()
{
	traversable = true;
	startTile = true;
	endTile = false;
	tileVisualization = 'S';
	playerOnTile = false;
}

TileStart::~TileStart()
{
}

bool TileStart::isTraversable() const
{
	return true;
}

bool TileStart::isStartTile() const
{
	return true;
}

char TileStart::getTileVisualization() const
{
	return tileVisualization;
}
