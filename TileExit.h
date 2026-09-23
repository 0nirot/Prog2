#pragma once
#include "Tile.h"

class TileExit : public Tile
{
public:
	TileExit();
	~TileExit();

	bool isTraversable() const override;
	bool isEndTile() const override;
	char getTileVisualization() const override;
};
