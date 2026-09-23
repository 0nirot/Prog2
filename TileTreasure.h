#pragma once
#include "Tile.h"
#include <memory>
#include "Items\ItemBase.h"

class TileTreasure : public Tile
{
public:
	TileTreasure();
	~TileTreasure();

	bool isTraversable() const override;
	Color getTileVisualization() const override;
	void traverse() override;

	void setLoot(std::unique_ptr<ItemBase> item);
	std::shared_ptr<ItemBase> getLoot() const;

private:
	std::unique_ptr<ItemBase> loot;

};
