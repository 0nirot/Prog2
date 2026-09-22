#include "ItemTrinket.h"

ItemTrinket::ItemTrinket()
	: ItemEquippable("Magic Ring", "Ein magischer Ring", 0.1f, 50), magicBonus(5)
{
}

ItemTrinket::ItemTrinket(const std::string& name, const std::string& description, float weight, int value, int magicBonus)
	: ItemEquippable(name, description, weight, value), magicBonus(magicBonus)
{
}

ItemTrinket::~ItemTrinket()
{
}

int ItemTrinket::getMagicBonus() const
{
	return magicBonus;
}

void ItemTrinket::setMagicBonus(int magicBonus)
{
	this->magicBonus = magicBonus;
}
