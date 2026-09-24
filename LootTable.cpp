#include "LootTable.h"
#include "utils.h"
#include "Items/Apple.h"
#include "Items/Axe.h"
#include "Items/Coin.h"
#include "Items/EmeraldRing.h"
#include "Items/IronArmor.h"
#include "Items/ItemSword.h"
#include "Items/Stick.h"
#include "Items/Sword.h"
#include "Items/Torch.h"
#include "Items/WoodenAmulet.h"
#include "PlotArmor.h"

LootTable::LootTable()
{
	items.push_back(std::make_unique<Apple>());
	items.push_back(std::make_unique<Axe>());
	items.push_back(std::make_unique<Coin>());
	items.push_back(std::make_unique<EmeraldRing>());
	items.push_back(std::make_unique<IronArmor>());
	items.push_back(std::make_unique<Stick>());
	items.push_back(std::make_unique<Sword>());
	items.push_back(std::make_unique<Torch>());
	items.push_back(std::make_unique<WoodenAmulet>());
	items.push_back(std::make_unique<PlotArmor>());
}

LootTable::~LootTable()
{
}


ItemBase* LootTable::getItem(int index) const
{
	if (index < 0 || index >= static_cast<int>(items.size()))
		return nullptr;
	return items[index].get();
}


void LootTable::removeItem(int index)
{
	if (index >= 0 && index < static_cast<int>(items.size()))
	{
		items.erase(items.begin() + index);
	}
}


std::unique_ptr<ItemBase> LootTable::getRandomItem() const
{
	if (items.empty())
		return nullptr;

	int randIndex = utils::trueRand(0, static_cast<int>(items.size()) - 1);

	return items[randIndex]->clone();
}
