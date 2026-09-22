#pragma once
#include "Tile.h"

class TileStart : public Tile
{
public:
	TileStart();
	~TileStart();

	bool isTraversable() const override;
	bool isStartTile() const override;
	char getTileVisualization() const override;
};
