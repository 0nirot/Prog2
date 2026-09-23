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

void TileTreasure::traverse()
{
	printf("%s\n", loot->getName().c_str());
}

void TileTreasure::setLoot(std::unique_ptr<ItemBase> item)
{
	loot = std::move(item);
}

std::shared_ptr<ItemBase> TileTreasure::getLoot() const
{
	return std::shared_ptr<ItemBase>(loot.get());
}