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

	// Übernimmt den Besitz des Items (unique_ptr wird implizit zu shared_ptr)
	void setLoot(std::shared_ptr<ItemBase> item);
	// Gibt den geteilten Besitz weiter, damit das Item das Tile überlebt
	std::shared_ptr<ItemBase> getLoot() const;

private:
	std::shared_ptr<ItemBase> loot;

};
