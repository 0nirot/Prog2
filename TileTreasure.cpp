#include "TileTreasure.h"

TileTreasure::TileTreasure()
{
	traversable = true;
	tileVisualization = 'T';
}

TileTreasure::~TileTreasure()
{
}

bool TileTreasure::isTraversable() const
{
	return true;
}

char TileTreasure::getTileVisualization() const
{
	return tileVisualization;
}
