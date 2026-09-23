#pragma once
#include "Tile.h"

class TileTreasure : public Tile
{
public:
	TileTreasure();
	~TileTreasure();

	bool isTraversable() const override;
	Color getTileVisualization() const override;
};
