#pragma once
#include "Tile.h"

class TileBlocked : public Tile
{
public:
	TileBlocked();
	~TileBlocked();

	bool isTraversable() const override;
	Color getTileVisualization() const override;
};
