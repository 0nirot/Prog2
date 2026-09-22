#pragma once
#include "Tile.h"

class TileTraversable : public Tile
{
public:
	TileTraversable();
	~TileTraversable();

	bool isTraversable() const override;
	char getTileVisualization() const override;
};
