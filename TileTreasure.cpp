#include "TileTreasure.h"

TileTreasure::TileTreasure()
{
	traversable = true;
	tileVisualization = GOLD;
}

TileTreasure::~TileTreasure()
{
}

bool TileTreasure::isTraversable() const
{
	return true;
}

Color TileTreasure::getTileVisualization() const
{
	return tileVisualization;
}
