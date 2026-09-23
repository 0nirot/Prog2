#pragma once
#include <vector>
#include <memory>
#include "Items/ItemBase.h"

class LootTable
{
public:
	LootTable();
	~LootTable();

	ItemBase* getItem(int index) const;

	void removeItem(int index);

	std::unique_ptr<ItemBase> getRandomItem() const;

private:
	std::vector<std::unique_ptr<ItemBase>> items;
};
