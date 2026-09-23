#pragma once
#include "Tile.h"
#include "ItemBase.h"

class TileTreasure : public Tile
{
public:
	TileTreasure();
	~TileTreasure();

	bool isTraversable() const override;
	Color getTileVisualization() const override;

private:
	//std::unique_ptr<ItemBase> loot;

};
