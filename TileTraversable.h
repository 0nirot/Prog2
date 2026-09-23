#pragma once
#include "Tile.h"

class TileTraversable : public Tile
{
public:
	TileTraversable();
	~TileTraversable();

	bool isTraversable() const override;
	Color getTileVisualization() const override;
};
