#pragma once
#include "Tile.h"

class TileBlocked : public Tile
{
public:
	TileBlocked();
	~TileBlocked();

	bool isTraversable() const override;
	char getTileVisualization() const override;
};
